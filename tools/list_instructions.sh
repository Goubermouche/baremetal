# !/bin/bash 
# prints unique used instructions

SCRIPT_DIR="$(dirname "$(realpath "$0")")"

node "$SCRIPT_DIR/scripts/instlist.js" "$SCRIPT_DIR/scripts/db.json"

