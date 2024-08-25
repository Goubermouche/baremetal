# !/bin/bash 

# regenerates all automatically generated files, including: 
# - db.json
# - instruction_database.inc

sh ./convert_db.sh
sh ./table_generator.sh

