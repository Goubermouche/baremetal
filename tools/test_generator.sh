# !/bin/bash 
# generates tests for all instructions in db.json

SCRIPT_DIR="$(dirname "$(realpath "$0")")"

node "$SCRIPT_DIR/scripts/testgen.js" "$SCRIPT_DIR/scripts/db.json" "$SCRIPT_DIR/../tests/encoding/" "$SCRIPT_DIR"
 
