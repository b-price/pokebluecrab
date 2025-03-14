#!/usr/bin/env python3
import os
import shutil
import argparse
import json

# Constants for directories
MAPS_DIR = "maps/"
LAYOUTS_DIR = "layouts/"


def recursive_replace_json(obj, old_name, new_name, on_upper, nn_upper):
    """
    Recursively process a JSON structure and perform the following string replacements:
      - MAPSEC_{on_upper} -> MAPSEC_{nn_upper}
      - MAP_{on_upper}    -> MAP_{nn_upper}
      - {old_name}        -> {new_name}
      - LAYOUT_{on_upper} -> LAYOUT_{nn_upper}
    """
    if isinstance(obj, str):
        s = obj.replace(f"MAPSEC_{on_upper}", f"MAPSEC_{nn_upper}")
        s = s.replace(f"MAP_{on_upper}", f"MAP_{nn_upper}")
        s = s.replace(f"{old_name}", f"{new_name}")
        s = s.replace(f"LAYOUT_{on_upper}", f"LAYOUT_{nn_upper}")
        return s
    elif isinstance(obj, list):
        return [recursive_replace_json(item, old_name, new_name, on_upper, nn_upper) for item in obj]
    elif isinstance(obj, dict):
        new_obj = {}
        for k, v in obj.items():
            new_obj[k] = recursive_replace_json(v, old_name, new_name, on_upper, nn_upper)
        return new_obj
    else:
        return obj


def update_layouts_json(new_layout_entries):
    """
    For each tuple (new_folder_name, layout_name_upper, on_upper, nn_upper) in new_layout_entries:
      - Load layouts.json (which is a JSON object with a "layouts" array).
      - Find an entry in layouts["layouts"] with "id": "LAYOUT_{on_upper}".
      - If found, append a new entry to the array with:
            "id": layout_name_upper,
            "name": "{new_folder_name}_Layout",
            "width": (from old entry),
            "height": (from old entry),
            "primary_tileset": (from old entry),
            "secondary_tileset": (from old entry),
            "border_filepath": "data/layouts/{new_folder_name}/border.bin",
            "blockdata_filepath": "data/layouts/{new_folder_name}/map.bin"
    """
    layouts_json_path = os.path.join(LAYOUTS_DIR, "layouts.json")
    try:
        with open(layouts_json_path, "r", encoding="utf-8") as f:
            layouts_data = json.load(f)
    except Exception as e:
        print(f"Failed to load {layouts_json_path} as JSON: {e}")
        return

    # Access the layouts list from the known format.
    layouts_list = layouts_data.get("layouts", [])

    for new_folder_name, layout_name_upper, on_upper, nn_upper in new_layout_entries:
        target_id = f"LAYOUT_{on_upper}"
        old_entry = next((entry for entry in layouts_list if entry.get("id") == target_id), None)
        if old_entry is None:
            print(f"No matching old layout entry with id {target_id} found for folder {new_folder_name}.")
            continue

        new_entry = {
            "id": layout_name_upper,
            "name": f"{new_folder_name}_Layout",
            "width": old_entry.get("width"),
            "height": old_entry.get("height"),
            "primary_tileset": old_entry.get("primary_tileset"),
            "secondary_tileset": old_entry.get("secondary_tileset"),
            "border_filepath": f"data/layouts/{new_folder_name}/border.bin",
            "blockdata_filepath": f"data/layouts/{new_folder_name}/map.bin"
        }
        print(f"Adding new layout entry for {layout_name_upper} based on {target_id} for folder {new_folder_name}.")
        layouts_list.append(new_entry)

    # Save back the updated layouts data.
    layouts_data["layouts"] = layouts_list
    try:
        with open(layouts_json_path, "w", encoding="utf-8") as f:
            json.dump(layouts_data, f, indent=2)
    except Exception as e:
        print(f"Failed to write updated layouts.json: {e}")


def update_mapgroups_json(new_maps_folder_names, new_name):
    """
    Opens mapgroups.json (in the maps directory) and appends each new maps folder name to the array
    found under the key "gMapGroup_Indoor{new_name}" (if that key exists).
    """
    mapgroups_json_path = os.path.join(MAPS_DIR, "map_groups.json")
    try:
        with open(mapgroups_json_path, "r", encoding="utf-8") as f:
            mapgroups_data = json.load(f)
    except Exception as e:
        print(f"Failed to load {mapgroups_json_path} as JSON: {e}")
        return

    key = f"gMapGroup_Indoor{new_name}"
    if key in mapgroups_data and isinstance(mapgroups_data[key], list):
        for folder_name in new_maps_folder_names:
            if folder_name not in mapgroups_data[key]:
                mapgroups_data[key].append(folder_name)
                print(f"Added folder '{folder_name}' to mapgroups under key '{key}'.")
    else:
        print(f"Key '{key}' not found in {mapgroups_json_path}; skipping mapgroups update.")

    try:
        with open(mapgroups_json_path, "w", encoding="utf-8") as f:
            json.dump(mapgroups_data, f, indent=2)
    except Exception as e:
        print(f"Failed to write updated mapgroups.json: {e}")


def update_event_scripts(new_maps_folder_names):
    """
    For each new maps folder, append a line to event_scripts.s (in the root directory)
    in the format:
         .include "data/maps/{new_folder_name}/scripts.inc"
    """
    event_scripts_path = "event_scripts.s"
    try:
        with open(event_scripts_path, "a", encoding="utf-8") as f:
            for folder_name in new_maps_folder_names:
                include_line = f'.include "data/maps/{folder_name}/scripts.inc"\n'
                f.write(include_line)
                print(f"Appended include line for folder '{folder_name}' to event_scripts.s")
    except Exception as e:
        print(f"Failed to update {event_scripts_path}: {e}")


def copy_and_replace(old_name, new_name, on_upper, nn_upper):
    # List of directories to process
    parent_dirs = [MAPS_DIR, LAYOUTS_DIR]

    # For maps folders, record tuples: (new_folder_name, new_folder_path, layout_name_upper)
    new_maps_info = []

    for parent in parent_dirs:
        if not os.path.isdir(parent):
            print(f"Directory '{parent}' does not exist. Skipping.")
            continue

        for entry in os.listdir(parent):
            entry_path = os.path.join(parent, entry)
            if os.path.isdir(entry_path):
                if f"{old_name}_" in entry:
                    print(f"Copying {entry} to {new_name}")
                    new_folder_name = entry.replace(old_name, new_name)
                    new_folder_path = os.path.join(parent, new_folder_name)
                    print(f"Copying from '{entry_path}' to '{new_folder_path}'...")
                    shutil.copytree(entry_path, new_folder_path, dirs_exist_ok=True)

                    if parent == MAPS_DIR:
                        new_maps_info.append((new_folder_name, new_folder_path, None))

    # Process each new maps folder's JSON and scripts.
    updated_maps_info = []
    for new_folder_name, new_folder_path, _ in new_maps_info:
        json_path = os.path.join(new_folder_path, "map.json")
        layout_name_upper = None
        if os.path.isfile(json_path):
            print(f"Updating JSON in '{json_path}'...")
            try:
                with open(json_path, "r", encoding="utf-8") as f:
                    data = json.load(f)
            except Exception as e:
                print(f"Failed to parse JSON in {json_path}: {e}")
                data = None
            if data is not None:
                original_layout = data.get("layout")
                new_data = recursive_replace_json(data, old_name, new_name, on_upper, nn_upper)
                new_layout = new_data.get("layout")
                if original_layout and new_layout and original_layout != new_layout:
                    layout_name_upper = new_layout.upper()
                    print(
                        f'Layout field changed in {json_path}: "{original_layout}" -> "{new_layout}" (stored as "{layout_name_upper}")')
                with open(json_path, "w", encoding="utf-8") as f:
                    json.dump(new_data, f, indent=2)
        # Process scripts.inc similarly (plain text replacement is acceptable here)
        scripts_path = os.path.join(new_folder_path, "scripts.inc")
        if os.path.isfile(scripts_path):
            print(f"Updating scripts in '{scripts_path}'...")
            with open(scripts_path, "r", encoding="utf-8") as f:
                content = f.read()
            content = content.replace(f"{old_name}", f"{new_name}")
            with open(scripts_path, "w", encoding="utf-8") as f:
                f.write(content)
        updated_maps_info.append((new_folder_name, new_folder_path, layout_name_upper))

    # Update layouts.json for folders that had a changed layout.
    new_layout_entries = []
    for new_folder_name, new_folder_path, layout_name_upper in updated_maps_info:
        if layout_name_upper:
            new_layout_entries.append((new_folder_name, layout_name_upper, on_upper, nn_upper))
    if new_layout_entries:
        update_layouts_json(new_layout_entries)

    # Update mapgroups.json with new maps folder names.
    new_maps_folder_names = [info[0] for info in updated_maps_info]
    update_mapgroups_json(new_maps_folder_names, new_name)

    # Append include lines to event_scripts.s for each new maps folder.
    update_event_scripts(new_maps_folder_names)

    print("Processing complete.")


def main():
    parser = argparse.ArgumentParser(
        description="Copy folders and update map.json, layouts.json, and map_groups.json."
    )
    parser.add_argument("old_name", help="Old name to be replaced")
    parser.add_argument("new_name", help="New name to use in replacement")
    parser.add_argument("on_upper", help="Uppercase old name")
    parser.add_argument("nn_upper", help="Uppercase new name")
    args = parser.parse_args()

    copy_and_replace(args.old_name, args.new_name, args.on_upper, args.nn_upper)


if __name__ == "__main__":
    main()
