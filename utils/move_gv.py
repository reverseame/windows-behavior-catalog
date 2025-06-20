# RazviOverflow
# Script that moves the corresponding .gv (graphviz) files from a given folder to their corresponding folder in the behavior catalog based on their .exe name.
# This script only works with a folder containing the per-report analysis as generated by our module.

import pathlib
import json
import argparse

behavior_catalog_exe_paths = {}
behavior_catalog_exe_categories = {}

# What .gv categories should be copied to the behavior catalog directory
# based on the category of the .exe file. Notice there are two different levels,
# the micro-objective (generic) and the micro-behavior (specific)
catalog_categories_to_gv_categories_mapping = {
	"[OC0001] Filesystem":[
		"Files and I_O (Local file system)" # Notice I_O instead of I/O, since our module replaces "/" with "_" to avoid directory naming problems
		],
	"[OC0005] Cryptography":[
		"Cryptography", 
		"Cryptographic Next Generation (CNG)",
		"CNG Cryptographic Primitive",
		],
	"[OC0006] Communication":[
		"Network Management", 
		"Windows Networking (WNet)", 
		"Windows Internet (WinINet)",
		"Windows Sockets (Winsock)",
		],
	"[OC0002] Memory":[
		"Memory Management"
		],
	"[OC0003] Process":[
		"Processes",
		],
	"[C0042] Create Mutex":[
		"Synchronization"
		],
	"[C0043] Check Mutex":[
		"Synchronization"
		],
	"[C0036] Registry":[
		"Registry"
		],
	"[C0034] Environment Variable":[
		"System Information Functions"
		],
}

BEHAVIOR_CATALOG_PATH = ""
REPORTS_FOLDER_PATH = ""

def usage():
	usage = "\nUse this tool to automatically classify and move the corresponding .gv (graphviz) files to their corresponding behavior catalog folder."
	usage += "\nPlease bear in mind the classification is done using the .exe files name as reference. "
	usage += "That is, the .exe program name in the name of each .gv file file is located in the behavior catalog.\n"
	usage += "This script only works with a folder containing the per-report analysis as generated by our tool MalGraphIQ (https://github.com/reverseame/MalGraphIQ).\n"
	usage += "\nSyntax: move_reports.py {BEHAVIOR_CATALOG_PATH} {REPORTS_FOLDER_PATH}. Examples:\n"
	usage += "\tmove_reports.py /home/user/behavior_catalog home/user/reports\n"
	usage += "\tmove_reports.py ./behavior_catalog ../../../reports\n"
	return usage

def parse_arguments():
    parser = argparse.ArgumentParser(description="Tool used to move the reports from a given folder to their corresponding folder in the behavior catalog.", usage=usage())
    parser.add_argument("BEHAVIOR_CATALOG_PATH", help="Path to the behavior catalog folder, as downloaded from GitHub.")
    parser.add_argument("REPORTS_FOLDER_PATH", help="Path to the folder containing all the reports in json format as downloaded from CAPEv2.")
    arguments = parser.parse_args()
    return arguments

if __name__ == "__main__":
	arguments = parse_arguments()

	BEHAVIOR_CATALOG_PATH = arguments.BEHAVIOR_CATALOG_PATH
	REPORTS_FOLDER_PATH = arguments.REPORTS_FOLDER_PATH

	# Get all .exe files from the behavior catalog along their path and category
	for exe_file in pathlib.Path(BEHAVIOR_CATALOG_PATH).rglob("*.exe"):
		exe_name = exe_file.absolute().name # FindFirstFile.exe
		exe_path = exe_file.absolute().parent.parent # Abspath. Double .parent call to get rid of the /exe folder.
		behavior_catalog_exe_paths[exe_name] = exe_path.as_posix()

		# The category of this binary and its gv mapping depend on whether is micro-behavior
		# level is specified in the 'catalog_categories_to_gv_categories_mapping' dict or
		# just its micro-objective level
		micro_objective = exe_path.parent.as_posix()
		micro_objective = micro_objective[micro_objective.index("[C"):] # "[C" is for micro-behaviors
		category = micro_objective if micro_objective in catalog_categories_to_gv_categories_mapping else exe_path.parent.parent.as_posix()
		category = category[category.index("["):]
		behavior_catalog_exe_categories[exe_name] = category

	# Get all .gv files from reports folder containing the .exe and its categories + .gv in ints name
	for exe in behavior_catalog_exe_paths:
		exe_category = behavior_catalog_exe_categories[exe]
		for cape_category in catalog_categories_to_gv_categories_mapping[exe_category]:
			for gv_file in pathlib.Path(REPORTS_FOLDER_PATH).rglob(f"*{exe}*{cape_category}*.gv"):
				#print(gv_file)
				gv_file_name = gv_file.name
				gv_file_name = gv_file_name[:gv_file_name.index(".exe")] + ".exe"
				new_gv_file_path = behavior_catalog_exe_paths[gv_file_name]
				#print(f"{gv_file_name} belongs to: {new_gv_file_path}")
				try:
					new_path = f"{new_gv_file_path}/gv/{gv_file.name}"
				except Exception as e:
					print("[!] ERROR: " + type(e).__name__ + " " + str(e) + ". SKIPPING [!]")
					continue
				new_path_object = pathlib.Path(new_path)
				new_path_object.parent.mkdir(parents=True, exist_ok=True) # Create containing folder if it does not exist
				gv_file.rename(pathlib.Path(new_path))
				print(f"Moved {gv_file} to {new_path}")
		'''
		with open(report) as report_file:
			json_report = json.load(report_file)
			report_exe = json_report["target"]["file"]["name"]
			try:
				new_path = f"{behavior_catalog_exe_paths[report_exe]}/reports/{report.name}"
			except Exception as e:
				print("[!] ERROR: " + type(e).__name__ + " " + str(e) + ". SKIPPING [!]")
				continue
			if not report.name.endswith(".json"):
				new_path += ".json"
			new_path_object = pathlib.Path(new_path)
			new_path_object.parent.mkdir(parents=True, exist_ok=True) # Create containing folder if it does not exist
			report.rename(pathlib.Path(new_path))
			print(f"Moved {report} to {new_path}")
		'''
