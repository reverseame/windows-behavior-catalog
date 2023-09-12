# RazviOverflow
# Script that moves reports from a given folder to their corresponding folder in the behavior catalog based on their process name.

import pathlib
import sys
import json

behavior_catalog_exe_paths = {}

for exe_file in pathlib.Path("../").rglob("*.exe"):
	exe_name = exe_file.absolute().name # FindFirstFile.exe
	exe_path = exe_file.absolute().parent.parent.as_posix() # Abspath. Double .parent call to get rid of the /exe folder.
	behavior_catalog_exe_paths[exe_name] = exe_path

#print(behavior_catalog)

for report in pathlib.Path(sys.argv[1]).glob("*"):
	with open(report) as report_file:
		json_report = json.load(report_file)
		report_exe = json_report["target"]["file"]["name"]
		new_path = f"{behavior_catalog_exe_paths[report_exe]}/reports/{report.name}"
		if not report.name.endswith(".json"):
			new_path += ".json"
		new_path_object = pathlib.Path(new_path)
		new_path_object.parent.mkdir(parents=True, exist_ok=True) # Create containing folder if it does not exist
		report.rename(pathlib.Path(new_path))
		print(f"Moved {report} to {new_path})