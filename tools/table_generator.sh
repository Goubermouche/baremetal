# !/bin/bash 
# generates instruction_database.inc from db.json

SCRIPT_DIR="$(dirname "$(realpath "$0")")"

node "$SCRIPT_DIR/scripts/tablegen.js" "$SCRIPT_DIR/scripts/db.json" > "$SCRIPT_DIR/../source/assembler/instruction/databases/database.inc"

