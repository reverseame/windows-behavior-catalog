import json
import argparse
from collections import defaultdict

def parse_arguments():
    parser = argparse.ArgumentParser(description="Script used generate statistics from the WBC in JSON format")
    parser.add_argument("wbc_json_path", help="Path of the WBC in JSON format (the .json file).")
    arguments = parser.parse_args()
    return arguments

def analyze_json(json_file):
    with open(json_file, 'r') as file:
        data = json.load(file)

    micro_objective_count = 0
    micro_behavior_count = 0
    method_count = 0
    pattern_lengths = []

    # Recursive function to traverse the nested JSON structure
    def traverse_json(obj, level=0):
        nonlocal micro_objective_count, micro_behavior_count, method_count

        if isinstance(obj, dict):
            for key, value in obj.items():
                # Level 0 -> Micro-objectives
                # Level 1 -> Micro-behaviors
                # Level 2 -> Methods 
                # Level 3 -> Patterns
                if level == 0:
                    micro_objective_count += 1
                elif level == 1:
                    micro_behavior_count += 1
                elif level == 2:
                    method_count += 1
                traverse_json(value, level + 1)

        elif isinstance(obj, list):  # Pattern level
            pattern_lengths.append(len(obj))

    # Traverse the JSON data
    traverse_json(data)

    # Calculate statistics
    stats = {
        "Total Micro-objectives": micro_objective_count,
        "Total Micro-behaviors": micro_behavior_count,
        "Total Methods": method_count,
        "Total Patterns": len(pattern_lengths),
        "Minimum Pattern Length": min(pattern_lengths) if pattern_lengths else 0,
        "Maximum Pattern Length": max(pattern_lengths) if pattern_lengths else 0
    }

    # Print the results
    print("\n=== WBC Statistical Analysis ===")
    for key, value in stats.items():
        print(f"{key}: {value}")

    return stats

# Example usage
if __name__ == "__main__":
    arguments = parse_arguments()
    analyze_json(arguments.wbc_json_path)
