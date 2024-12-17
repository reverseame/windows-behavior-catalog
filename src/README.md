# Creation of the Windows Behavior Catalog (WBC)
The [create_behavior_catalog.py](./create_behavior_catalog.py) tool is used to automatically generate the patterns and organize them in the corresponding tree-like structure. That is, the catalog itself. It parses the files contained in this repository (or any other directory specified by the user) and automatically reads the `.gv` files, from which it computes the different paths and patterns. 

Usage example:

- `python3 create_behavior_catalog.py ../ > ../catalog.json` generate the catalog in JSON format, redirecting stdout to ../catalog.json.
- `python3 create_behavior_catalog.py -t ../ > ../catalog.txt` generate the catalog in text format, redirecting stdout to ../catalog.txt.
- `python3 create_behavior_catalog.py ${directory_of_your_choice}` generate the catalog in JSON format, printing it to stdout.