# !/bin/bash 

# regenerates all automatically generated files, including: 
# - db.json
# - instruction_database.inc

SCRIPT_DIR="$(dirname "$(realpath "$0")")"

bash "$SCRIPT_DIR/convert_db.sh"
bash "$SCRIPT_DIR/table_generator.sh"

