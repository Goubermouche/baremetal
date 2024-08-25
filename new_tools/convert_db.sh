# !/bin/bash 
# converts the AsmJit database into our own version

node ./scripts/db_converter.js ./scripts/asmjit_db.json > ./scripts/db.json

