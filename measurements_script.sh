#!/bin/bash

dim="$1"
itr="$2"
file="$3"

[ $# -eq 0 ] && { exit 1; }

if [ -f "$file""$dim"_"$itr".txt ]
then 
	sudo rm "$file""$dim"_"$itr".txt
fi
echo "pure openmp\n" >> "$file""$dim"_"$itr".txt
sh no-gui-run.sh parallel-no-gui 1 1 "$dim" "$itr" >> "$file""$dim"_"$itr".txt
sh no-gui-run.sh parallel-no-gui 1 2 "$dim" "$itr" >> "$file""$dim"_"$itr".txt
sh no-gui-run.sh parallel-no-gui 1 3 "$dim" "$itr" >> "$file""$dim"_"$itr".txt
sh no-gui-run.sh parallel-no-gui 1 4 "$dim" "$itr" >> "$file""$dim"_"$itr".txt
sh no-gui-run.sh parallel-no-gui 1 5 "$dim" "$itr" >> "$file""$dim"_"$itr".txt
sh no-gui-run.sh parallel-no-gui 1 6 "$dim" "$itr" >> "$file""$dim"_"$itr".txt
sh no-gui-run.sh parallel-no-gui 1 7 "$dim" "$itr" >> "$file""$dim"_"$itr".txt
sh no-gui-run.sh parallel-no-gui 1 8 "$dim" "$itr" >> "$file""$dim"_"$itr".txt
echo "hybrid\n" >> "$file""$dim"_"$itr".txt
sh no-gui-run.sh parallel-no-gui 2 1 "$dim" "$itr" >> "$file""$dim"_"$itr".txt
sh no-gui-run.sh parallel-no-gui 2 2 "$dim" "$itr" >> "$file""$dim"_"$itr".txt
sh no-gui-run.sh parallel-no-gui 2 3 "$dim" "$itr" >> "$file""$dim"_"$itr".txt
sh no-gui-run.sh parallel-no-gui 2 4 "$dim" "$itr" >> "$file""$dim"_"$itr".txt
sh no-gui-run.sh parallel-no-gui 3 1 "$dim" "$itr" >> "$file""$dim"_"$itr".txt
sh no-gui-run.sh parallel-no-gui 3 2 "$dim" "$itr" >> "$file""$dim"_"$itr".txt
sh no-gui-run.sh parallel-no-gui 4 1 "$dim" "$itr" >> "$file""$dim"_"$itr".txt
sh no-gui-run.sh parallel-no-gui 4 2 "$dim" "$itr" >> "$file""$dim"_"$itr".txt
