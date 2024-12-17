import json
import argparse
import os
import copy
import networkx as nx
import logging

from patterns_paths_and_nodes import *

# Constants
OTHERS_NODE = "others"
START_NODE = "Start"
COMMANDLINE_PREFIX = "GetCommandLine"

# Set up logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

def parse_arguments():
    parser = argparse.ArgumentParser(
        description=(
            "Script used to create the Windows Behavior Catalog (WBC). " 
            "Usage example: python3 create_behavior_catalog.py ../ > ../catalog.json"
        )
    )
    parser.add_argument("behavior_catalog_directory", 
        help=(
            "The directory containing the gv files corresponding to each behavior. "
            "The structure of the directory must follow the MBC (Malware Behavior Catalog) structure. "
            "See: https://github.com/RazviOverflow/behaviors (clone and use this repo)."
        )
    )
    parser.add_argument("-t", "--text", 
        action='count', 
        help="Output in text form (tab-indented). By default the output is in JSON.")
    parser.add_argument("--print_discarded", 
        action='count', 
        help="Prints only the discarded simple_paths (in JSON format). That is, those made up of a single node.")

    return parser.parse_args()

def get_start_node(g: nx.classes.digraph.DiGraph) -> str:
    """
    Get the first node of the graph, which must have peripheries == "2".

    Args:
        g (nx.classes.digraph.DiGraph): The graph to process.

    Returns:
        str: The start node ID, first node of graph _g_.
    """
    nodes_iterator = iter(g._node)
    first_node = next(nodes_iterator)
    # Start node should also be the first one and the only one with peripheries
    assert(g._node[first_node]["peripheries"] == "2") 
    return first_node

def node_already_in_paths(paths: list, node: str) -> bool:
    """
    Check if node _node_ exists in any path from _paths_.

    Parameters:
        paths (list): List of paths.
        node (list): Node to check.

    Returns:
        bool: True if _node_ is in any path from _paths_, False otherwise.
    """
    for path in paths:
        if node in path:
            return True
    return False

def filter_simple_paths(paths: list) -> list:
    """
    Filters the list paths by deleting all its elements (representing simple paths)
    present in the dict `paths_to_filter`, defined in the file patterns_paths_and_nodes.py. 

    Additionally, this function also deletes the sequence GetCommandLineA, GetCommandLineW
    from the beginning of the path.

    Parameters:
        paths (list): The list to filter, where each element is a simple path.

    Returns:
        list: The filtered path list.
    """

   
    for i, simple_path in enumerate(paths):
        #if len(simple_path) >= 2 and simple_path[0] == 'GetCommandLine' and simple_path[1] == 'GetCommandLine':
        #    paths[i] = simple_path[2:]
        if len(simple_path) >= 1 and simple_path[0] == COMMANDLINE_PREFIX:
            paths[i] = simple_path[1:]


    new_paths = list()

    for path in paths:
        if str(path) not in paths_to_filter:
            new_paths.append(path)

    return new_paths
    
def get_simple_paths(g: nx.classes.digraph.DiGraph, start_node: str, min_length: int = 1) -> list:
    """
    Returns all the simple paths from start_node to 'others' node in graph g.

    If there are other nodes after the 'others' node (that is, 'others'
    node has successors), consider them as other individual paths
    from 'others' to 'others'. Then combine them to get every possible path.

    This function filters the irrelevant paths by invoking filter_simple_paths().

    Parameters:
        g (nx.classes.digraph.DiGraph): The category graph to get the categorical walk from.
        start_node (str): The 'Start' node, according to its id/label (they're the same).
        min_length (int): Minimum numbers of nodes the simple paths must have. Defaults to 1.

    Returns:
        list: All the simple paths from start_node to 'others' node in graph g.
    """
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

def get_unique_start_nodes(paths: list) -> list:
    """
    Extract unique start nodes from a list of paths.

    Args:
        paths (list): List of paths.

    Returns:
        list: List of unique start nodes.
    """
    start_nodes = []
    for path in paths:
        start_nodes.append(path[0])
    return list(set(start_nodes))

def print_catalog_json(catalog: dict) -> None:
    """
    Print catalog in JSON format.

    Args:
        catalog (dict): Catalog data.
    """
    print(json.dumps(catalog, indent=4))

def print_catalog_text(catalog: dict) -> None:
    """
    Print catalog in text format with indentation.

    Args:
        catalog (dict): Catalog data.
    """
    for micro_objective_name in catalog:
        print(micro_objective_name)
        for micro_behavior_name in catalog[micro_objective_name]:
            print("\t"+micro_behavior_name)
            for method in catalog[micro_objective_name][micro_behavior_name]:
                print("\t\t"+method)
                for pattern in catalog[micro_objective_name][micro_behavior_name][method]:
                    print(f"\t\t\t{pattern}:{catalog[micro_objective_name][micro_behavior_name][method][pattern]}")

def flatten(l: list[list]) -> list:
    """
    Flatten a list of lists.

    Args:
        l (list[list]): A list of lists.

    Returns:
        list: A flattened list.
    """
    return [item for sublist in l for item in sublist]

def contains(container: list, contained: list) -> tuple[int, int] | bool:
    """
    Check if a sequence is contained within another sequence.

    Args:
        container (list): The main sequence.
        contained (list): The sequence to search for.

    Returns:
        tuple[int, int] | bool: Range of indices if found, otherwise False.
    """
    small_length = len(contained)
    for i in range(len(container)-small_length+1):
        for j in range(small_length):
            if container[i+j] != contained[j]:
                break
        else:
            return i, i+small_length # i+small_lentgh is one position further than where it actually ends. I.e., range(i, i+small_length)
    return False

def create_catalog(path):
    """
    Create the Windows Behavior Catalog (WBC) by processing the main contents of the repository 
    and their corresponding graph patterns.

    Args:
        path (str): Path to the WBC directory.

    Returns:
        tuple[dict, dict]: Catalog dictionary and discarded patterns dictionary.
    """
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




    
    

