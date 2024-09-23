#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <puzzle_id>"
    exit 1
else
    echo "solving $1 puzzle:\n"
fi

PUZZLE_ID=$1
OUTPUT_FILE="puzzle_${PUZZLE_ID}.json"
curl "https://www.griddlers.net/pl_PL/nonogram/-/g/t1726003493075/i01?p_p_lifecycle=2&p_p_resource_id=griddlerPuzzle&p_p_cacheability=cacheLevelPage&_gpuzzles_WAR_puzzles_id=${PUZZLE_ID}&_gpuzzles_WAR_puzzles_lite=false&_gpuzzles_WAR_puzzles_name=touchScreen&_gpuzzles_WAR_puzzles_value=off" \
-H 'Accept: application/json, text/plain, */*' \
-H 'Cookie: [your_cookies_here]' \
-o "${OUTPUT_FILE}"

#now edit file and change it to json
sed -i '/palette: /,/],/d' "${OUTPUT_FILE}"
sed -i -n '/var puzzle = {/,/}/p' "${OUTPUT_FILE}"
sed -i 's/var puzzle = //' "${OUTPUT_FILE}"
sed -i '/hw:/d' "${OUTPUT_FILE}"
sed -i 's/^[[:space:]]*\([[:alpha:]_]\+\)/"\1"/' "${OUTPUT_FILE}"
sed -i 's/", *$/"/g' "${OUTPUT_FILE}"
