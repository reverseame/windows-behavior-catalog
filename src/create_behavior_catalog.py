import json
import argparse
import os
import copy
import networkx as nx
import logging

from patterns_paths_and_nodes import *

def parse_arguments():
    parser = argparse.ArgumentParser(description="Script used to create the Windows Behavior Catalog (WBC). Usage example: python3 create_behavior_catalog.py ../ > ../catalog.json")
    parser.add_argument("behavior_catalog_directory", help="The directory containing the gv files corresponding to each behavior. The structure of the directory must follow the MBC (Malware Behavior Catalog) structure. See: https://github.com/RazviOverflow/behaviors (clone and use this repo).")
    parser.add_argument("-t", "--text", action='count', help="Output in text form (tab-indented). By default the output is in JSON.")
    parser.add_argument("--print_discarded", action='count', help="Prints only the discarded simple_paths (in JSON format). That is, those made up of a single node. ")
    arguments = parser.parse_args()
    return arguments

def get_start_node(g: nx.classes.digraph.DiGraph):
    nodes_iterator = iter(g._node)
    first_node = next(nodes_iterator)
    # Start node should also be the first one and the only one with peripheries
    assert(g._node[first_node]["peripheries"] == "2") 
    return first_node

def already_in_paths(simple_paths, path):
    '''
    Returns whether a node from the path _path_ is in at least one of the paths in _paths_
    '''

    for aux_path in simple_paths:
        for node in path:
            if node in aux_path:
                return True
    return False

def node_already_in_paths(paths, node):
    '''
    Returns whether the node _node_ is in at least one of the paths in _paths_
    '''
    for path in paths:
        if node in path:
            return True
    return False

def filter_simple_paths(paths : list):
    '''
    Filters the list paths by deleting all its elements (representing simple paths)
    present in the dict `paths_to_filter`, defined in this file. 

    Additionally, this function also deletes the sequence GetCommandLineA, GetCommandLineW
    from the beginning of the path.

    Parameters:
        paths:
            The list to filter, where each element is a simple path.

    Returns:
        The filtered path list.
    '''

   
    for i, simple_path in enumerate(paths):
        #if len(simple_path) >= 2 and simple_path[0] == 'GetCommandLine' and simple_path[1] == 'GetCommandLine':
        #    paths[i] = simple_path[2:]
        if len(simple_path) >= 1 and simple_path[0] == 'GetCommandLine':
            paths[i] = simple_path[1:]


    new_paths = list()

    for path in paths:
        if str(path) not in paths_to_filter:
            new_paths.append(path)

    return new_paths
    
def get_simple_paths(g: nx.classes.digraph.DiGraph, start_node, min_length: int = 1):
    '''
    Returns all the simple paths from start_node to 'others' node in graph g.

    If there are other nodes after the 'others' node (that is, 'others'
    node has successors), consider them as other individual paths
    from 'others' to 'others'. Then combine them to get every possible path.

    This function filters the irrelevant paths by invoking filter_simple_paths()

    Parameters:
        g:
            The category graph to get the categorical walk from.
        start_node:
            The 'Start' node, according to its id/label (they're the same)
        min_length:
            Minimum numbers of nodes the simple paths must have. Defaults to 1.
    '''
    simple_paths = []
    # get direct paths from 'Start' to 'others'
    for path in nx.all_simple_paths(g, source=start_node, target='others'):
        path = path[:-1] # Eliminate the 'others' node from the path
        #path = path[1:-1] # Eliminate the first (source) and last (target) nodes from the path
        #path = path[1:]
        #if len(path) > 1: # avoid single-node paths
        simple_paths.append(path)

    # Calculate all the successors of 'Start' that are also predecessors of 'others'.
    # This way, the paths whose start node is 'others' get preffixed with these
    # intermediate nodes, generating a new path for each one of them. 
    # start_successors = g.successors('Start')
    # others_predecessors = g.predecessors('others')
    # beginning_nodes = [node for node in start_successors if node in others_predecessors]

    # Calculate all the simple paths from 'others' to 'others'. Combine with 
    # previously calculated simple paths
    concatenated_paths = []
    if 'others' in g:
        for node in g.successors('others'):
            if not node_already_in_paths(simple_paths, node):
                for path in nx.all_simple_paths(g, source=node, target='others'):
                    path = path[:-1] # we only need to remove here the target, not the source
                    #if len(path) > 1: # avoid single-node paths
                    #if not already_in_paths(simple_paths, path):
                    for simple_path in simple_paths:
                        concatenated_paths.append(simple_path + path)
                    
    # Now merge the lists and delete those whose length is lesser than min_length
    all_paths = simple_paths+concatenated_paths
    all_paths = filter_simple_paths(all_paths) 
    all_paths[:] = [path for path in all_paths if len(path) > min_length]

    return all_paths

def get_unique_start_nodes(paths):
    '''
    Returns a list with the final node of each path in paths (without repetition)
    '''
    start_nodes = []
    for path in paths:
        start_nodes.append(path[0])
    return list(set(start_nodes))

def get_end_nodes(paths):
    '''
    Returns a list with the final node of each path in paths
    '''
    end_nodes = []
    for path in paths:
        end_nodes.append(path[-1])
    
    # this could be a set instead of a list to avoid repeated end nodes (they are unneeded)
    return end_nodes

def is_path_feasible(g_behavior, path):
    '''
    Returns whether the path _path_ is feasible in graph _g_behavior_. That is,
    if all the nodes in _path_ are present in graph _g_behavior_.
    '''
    behavior_nodes = g_behavior.nodes()
    for node in path:
        if node not in behavior_nodes:
            #print(f"Node {node} not in behavior graph!")
            return False
    return True

def get_path_probability(g: nx.classes.multidigraph.MultiDiGraph , path: list, initial_probability = 1.0):
    '''
    Returns the probability of the path (sequence of connected nodes) _path_ given
    the graph _g_

    Parameters:
        g: nx.classes.multidigraph.MultiDiGraph
        path: list
        initial_probability = 1.0 (Optional)
    '''
    probability = initial_probability
    graph_nodes_adjacency = g._adj
    for src_node, dst_node in zip(path, path[1:]):
        probability *= float(graph_nodes_adjacency[src_node][dst_node][0]['label'])

    return probability

def get_all_paths_from_node_to_node_and_probabilities(graph, starting_node, destiny_node, probability_threshold):
    '''
    Returns a list of tuples containing each path from starting_node to destiny_node 
    in graph and the probability of each one of them. The returned list is in the
    form of: [[path, prob],[path, prob]] where each path is, in turn, a list of 
    nodes.
    
    Parameters:
        graph:
            The graph in to perform the operations with.
        starting_node:
            The node from which the path to seek will start.
        destiny_node:
            The node in which the path to seek will end.
        probability_threshold:
            The probability threshold to discard found paths.
    '''
    #paths = nx.single_source_dijkstra(graph, starting_node, destiny_node, weight=get_label_weight)
    #for i, simple_path in enumerate(nx.all_simple_paths(graph, starting_node, destiny_node, 8)):
    #    print(i, simple_path)

    ## CONFIGURATION PARAMETER: 'cutoff' -> This has a huge impact on the results.
    ## Based on our experiments, 5 is enough for the vast majority of the cases.
    paths = list(nx.all_simple_paths(graph, starting_node, destiny_node, 5)) # NEED TO LIMIT SOMEHOW THE LENGTH OF SIMPLE PATHS
    graph_nodes_adjacency = graph._adj
    all_paths = list()
    for path in paths:
        skip = False
        probability = 1.0
        for src_node, dst_node in zip(path, path[1:]):
            weight = graph_nodes_adjacency[src_node][dst_node][0]
            if 'label' in weight:
                probability *= float(weight['label'])
            # If the probability of the path so far is under the threshold, we omit
            # this path and skip to the next one
            if probability < probability_threshold:
                skip = True
                break
        #print(f"Probability is: {probability} and threshold: {PROBABILITY_THRESHOLD}")
        if not skip:
            all_paths.append((probability, path))
    #pprint(sorted(all_paths))
    #sys.exit()
    #for path in paths:
    #    pprint(path)
    return all_paths

def read_matrix_from_csv(file):
    # It is very important to specify which column is the index.
    transition_matrix = pd.read_csv(file, index_col=0) 
    return transition_matrix

def print_catalog_json(catalog):
    print(json.dumps(catalog, indent=4))

def print_catalog_text(catalog):
    for micro_objective_name in catalog:
        print(micro_objective_name)
        for micro_behavior_name in catalog[micro_objective_name]:
            print("\t"+micro_behavior_name)
            for method in catalog[micro_objective_name][micro_behavior_name]:
                print("\t\t"+method)
                for pattern in catalog[micro_objective_name][micro_behavior_name][method]:
                    print(f"\t\t\t{pattern}:{catalog[micro_objective_name][micro_behavior_name][method][pattern]}")

def flatten(l):
    return [item for sublist in l for item in sublist]

def contains(container, contained):
    small_length = len(contained)
    for i in range(len(container)-small_length+1):
        for j in range(small_length):
            if container[i+j] != contained[j]:
                break
        else:
            return i, i+small_length # i+small_lentgh is one position further than where it actually ends. I.e., range(i, i+small_length)
    return False

def create_catalog(path):
    catalog = {}
    discarded_patterns = {}
    # Get all patterns to delete
    repeated_patterns = {}
    compound_behaviors_values = flatten(compound_behaviors.values()) # Transform list of lists to just list
    micro_objectives = [os.path.join(path, file) for file in os.listdir(path)]
    for micro_objective in micro_objectives: # Micro-objective level
        micro_objective_name = os.path.basename(micro_objective)
        if micro_objective_name.startswith('[') and os.path.isdir(micro_objective):
            catalog[micro_objective_name] = {}
            discarded_patterns[micro_objective_name] = {}
            micro_behaviors = [os.path.join(micro_objective, file) for file in os.listdir(micro_objective)]
            for micro_behavior in micro_behaviors: # Micro-behavior level
                micro_behavior_name = os.path.basename(micro_behavior)
                if micro_behavior_name.startswith('[') and os.path.isdir(micro_behavior):
                    catalog[micro_objective_name][micro_behavior_name] = {}
                    discarded_patterns[micro_objective_name][micro_behavior_name] = {}
                    methods = os.listdir(micro_behavior)
                    for method in methods: # Method level
                        method = os.path.join(micro_behavior, method)
                        method_name = os.path.basename(method)
                        if method_name.startswith('[') and os.path.isdir(method):
                            catalog[micro_objective_name][micro_behavior_name][method_name] = {}
                            discarded_patterns[micro_objective_name][micro_behavior_name][method_name] = {}
                            method_id = method_name[1:method_name.index(']')]
                            try:
                                g_patterns = [os.path.join(method+"/gv", file) for file in os.listdir(method+"/gv")]
                            except Exception as e:
                                #print(f"[!] ERROR [!]: {e} - {e.args}")
                                #print("[!] SKIPPING [!]")
                                g_patterns = []
                            pattern_number = 1
                            discarded_pattern_number = 1
                            catalog[micro_objective_name][micro_behavior_name][method_name] = {}
                            discarded_patterns[micro_objective_name][micro_behavior_name][method_name] = {}
                            simple_paths = [] # All simple_paths for the method_name method
                            for g_pattern_name in g_patterns:
                                g_pattern = nx.nx_agraph.read_dot(g_pattern_name)
                                for simple_path in get_simple_paths(g_pattern, get_start_node(g_pattern), 0):
                                    #  Avoid duplicate patterns for the same method
                                    if simple_path not in simple_paths:
                                        simple_paths.append(simple_path) 
                                #for simple_path in simple_paths:
                                #    print(f"{g_pattern_name} - {simple_path}")
                                #for simple_path in get_simple_paths(g_pattern, get_start_node(g_pattern), 0): # min_simple_path_length = 0 to get all simple_paths
                            for simple_path in simple_paths:
                                if len(simple_path) >= 2:
                                    catalog[micro_objective_name][micro_behavior_name] \
                                    [method_name] [f"[{method_id}-P{pattern_number}]"] = simple_path
                                    pattern_number += 1
                                else:
                                    if str(simple_path) in included_single_nodes:
                                        catalog[micro_objective_name][micro_behavior_name] \
                                        [method_name] [f"[{method_id}-P{pattern_number}]"] = simple_path
                                        pattern_number += 1
                                    else:
                                        discarded_patterns[micro_objective_name][micro_behavior_name] \
                                        [method_name] [f"[{method_id}-P{discarded_pattern_number}]"] = simple_path
                                        discarded_pattern_number += 1
                            # Check if the pattern is one of those that must be later deleted because is included
                            # in any other one
                            if method_name in compound_behaviors_values:
                                repeated_patterns[method_name] = catalog[micro_objective_name][micro_behavior_name][method_name]

    # Check for compound behaviors and delete the patterns corresponding to another individual patterns
    for micro_objective in catalog:
        for micro_behavior in catalog[micro_objective]:
            for method in catalog[micro_objective][micro_behavior]:
                if method in compound_behaviors:
                    for individual_pattern in catalog[micro_objective][micro_behavior][method]:
                        pattern = catalog[micro_objective][micro_behavior][method][individual_pattern]
                        # If it is manually added, no need to re-process it
                        if not individual_pattern.endswith("H]"):
                            for compound_behavior in compound_behaviors[method]:
                                for repeated_pattern in repeated_patterns[compound_behavior].values():
                                    elements_range = contains(pattern, repeated_pattern)
                                    if elements_range: # If there are no occurrences, elements_range is false.
                                        start_index = int(elements_range[0])
                                        end_index = int(elements_range[1])
                                        for i in range(start_index, end_index):
                                            # Always delete start_index position because del modifies the whole list
                                            del pattern[start_index] 

                # Check if the method id has manually included patterns and insert them
                method_id = method[1:method.index(']')]
                if method_id in manually_included_patterns:
                    for pattern in manually_included_patterns[method_id]:
                        # Insert the pattern only if it isn't already present in the catalog
                        patterns_so_far = catalog[micro_objective][micro_behavior][method].values()
                        if pattern not in patterns_so_far:
                            # The pattern_number to be inserted is the number of patterns so far +1
                            pattern_number = len(patterns_so_far) + 1 
                            catalog[micro_objective][micro_behavior][method][f"[{method_id}-P{pattern_number}H]"] = pattern
                            pattern_number += 1                                            

    # One last traversal to delete empty patterns. deepcopy is employed
    catalog_copy = copy.deepcopy(catalog)
    for micro_objective in catalog_copy:
        for micro_behavior in catalog_copy[micro_objective]:
            for method in catalog_copy[micro_objective][micro_behavior]:
                if method in compound_behaviors:
                    for individual_pattern in catalog_copy[micro_objective][micro_behavior][method]:
                        pattern = catalog_copy[micro_objective][micro_behavior][method][individual_pattern]
                        # If patter is empty, delete it in the original catalog
                        if not len(pattern):
                            del catalog[micro_objective][micro_behavior][method][individual_pattern]

    return catalog, discarded_patterns


if __name__ == "__main__":
    arguments = parse_arguments()

    catalog, discarded = create_catalog(arguments.behavior_catalog_directory)

    if arguments.print_discarded:
        if arguments.text is None:
            print_catalog_json(discarded)
        else:
            print_catalog_text(discarded)
    else:
        if arguments.text is None:
            print_catalog_json(catalog)
        else:
            print_catalog_text(catalog)




    
    

