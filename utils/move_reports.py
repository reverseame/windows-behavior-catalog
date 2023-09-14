# RazviOverflow
# Script that moves reports from a given folder to their corresponding folder in the behavior catalog based on their process name.

import pathlib
import json
import argparse

behavior_catalog_exe_paths = {}
BEHAVIOR_CATALOG_PATH = ""
REPORTS_FOLDER_PATH = ""

def usage():
	usage = "\nUse this tool to automatically classify and move several reports.json to their corresponding behavior catalog folder."
	usage += "\nPlease bear in mind the classification is done using the .exe files name as reference. "
	usage += "That is, the program name in the report.json file is located in the behavior catalog.\n"
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

	for exe_file in pathlib.Path(BEHAVIOR_CATALOG_PATH).rglob("*.exe"):
		exe_name = exe_file.absolute().name # FindFirstFile.exe
		exe_path = exe_file.absolute().parent.parent.as_posix() # Abspath. Double .parent call to get rid of the /exe folder.
		behavior_catalog_exe_paths[exe_name] = exe_path

	#print(behavior_catalog)

	for report in pathlib.Path(REPORTS_FOLDER_PATH).glob("*"):
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