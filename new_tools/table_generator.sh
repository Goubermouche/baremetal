# !/bin/bash 
# generates instruction_database.inc from db.json

node ./scripts/tablegen.js ./scripts/db.json > ../source/assembler/instruction/databases/database.inc

