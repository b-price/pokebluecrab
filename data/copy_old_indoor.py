#!/usr/bin/env python3
import os
import shutil
import argparse

# Constants for directories
MAPS_DIR = "maps/"
LAYOUTS_DIR = "layouts/"


def copy_and_replace(old_name, new_name, on_upper, nn_upper):
    # List of directories to process
    parent_dirs = [MAPS_DIR, LAYOUTS_DIR]

    # Keep track of new folders created in the maps directory for the json replacement step.
    new_maps_folders = []

    for parent in parent_dirs:
        # Check that the directory exists
        if not os.path.isdir(parent):
            print(f"Directory '{parent}' does not exist. Skipping.")
            continue

        # Iterate over entries in the parent directory
        for entry in os.listdir(parent):
            entry_path = os.path.join(parent, entry)
            if os.path.isdir(entry_path):
                # Check if the folder name contains the pattern "old_name_"
                if f"{old_name}_" in entry:
                    print(f"Copying {entry} to {new_name}")
                    # Create the new folder name by replacing old_name with new_name
                    new_folder_name = entry.replace(old_name, new_name)
                    new_folder_path = os.path.join(parent, new_folder_name)

                    # Copy the folder recursively to the new location.
                    # dirs_exist_ok=True will merge if the destination exists (requires Python 3.8+)
                    print(f"Copying from '{entry_path}' to '{new_folder_path}'...")
                    shutil.copytree(entry_path, new_folder_path, dirs_exist_ok=True)

                    # If the folder is in the maps directory, record it for later processing.
                    if parent == MAPS_DIR:
                        new_maps_folders.append(new_folder_path)

    # Process each new maps folder for the JSON replacement.
    for folder in new_maps_folders:
        json_path = os.path.join(folder, "map.json")
        if os.path.isfile(json_path):
            print(f"Updating JSON in '{json_path}'...")
            # Read the file contents
            with open(json_path, "r", encoding="utf-8") as f:
                content = f.read()
            # Replace the strings as specified
            content = content.replace(f"MAPSEC_{on_upper}", f"MAPSEC_{nn_upper}")
            content = content.replace(f"MAP_{on_upper}", f"MAP_{nn_upper}")
            content = content.replace(f"{old_name}", f"{new_name}")
            content = content.replace(f"LAYOUT_{on_upper}", f"LAYOUT_{new_name}")
            # Write the updated contents back to the file
            with open(json_path, "w", encoding="utf-8") as f:
                f.write(content)

        scripts_path = os.path.join(folder, "scripts.inc")
        if os.path.isfile(scripts_path):
            print(f"Updating scripts in '{scripts_path}'...")
            # Read the file contents
            with open(scripts_path, "r", encoding="utf-8") as f:
                content = f.read()
            # Replace the strings as specified
            content = content.replace(f"{old_name}", f"{new_name}")
            # Write the updated contents back to the file
            with open(scripts_path, "w", encoding="utf-8") as f:
                f.write(content)

    print("Processing complete.")


def main():
    parser = argparse.ArgumentParser(description="Copy folders and update maps.json contents.")
    parser.add_argument("old_name", help="Old name to be replaced")
    parser.add_argument("new_name", help="New name to use in replacement")
    parser.add_argument("on_upper", help="uppercase old name")
    parser.add_argument("nn_upper", help="uppercase new name")
    args = parser.parse_args()

    copy_and_replace(args.old_name, args.new_name, args.on_upper, args.nn_upper)


if __name__ == "__main__":
    main()
