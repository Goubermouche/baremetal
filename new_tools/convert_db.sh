# !/bin/bash 
# converts the AsmJit database into our own version

SCRIPT_DIR="$(dirname "$(realpath "$0")")"

node "$SCRIPT_DIR/scripts/db_converter.js" "$SCRIPT_DIR/scripts/asmjit_db.json" > "$SCRIPT_DIR/scripts/db.json"

