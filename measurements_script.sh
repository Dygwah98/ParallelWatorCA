#!/bin/bash

dim="$1"
itr="$2"

[ $# -eq 0 ] && { exit 1; }

if [ -f output"$dim"_"$itr".txt ]
then 
	sudo rm output"$dim"_"$itr".txt
fi
sudo touch output"$dim"_"$itr".txt
sh no-gui-run.sh parallel-no-gui 1 1 "$dim" "$itr" >> output"$dim"_"$itr".txt
sh no-gui-run.sh parallel-no-gui 1 2 "$dim" "$itr" >> output"$dim"_"$itr".txt
sh no-gui-run.sh parallel-no-gui 1 3 "$dim" "$itr" >> output"$dim"_"$itr".txt
sh no-gui-run.sh parallel-no-gui 1 4 "$dim" "$itr" >> output"$dim"_"$itr".txt
sh no-gui-run.sh parallel-no-gui 1 5 "$dim" "$itr" >> output"$dim"_"$itr".txt
sh no-gui-run.sh parallel-no-gui 1 6 "$dim" "$itr" >> output"$dim"_"$itr".txt
sh no-gui-run.sh parallel-no-gui 1 7 "$dim" "$itr" >> output"$dim"_"$itr".txt
sh no-gui-run.sh parallel-no-gui 1 8 "$dim" "$itr" >> output"$dim"_"$itr".txt
sh no-gui-run.sh parallel-no-gui 2 1 "$dim" "$itr" >> output"$dim"_"$itr".txt
sh no-gui-run.sh parallel-no-gui 2 2 "$dim" "$itr" >> output"$dim"_"$itr".txt
sh no-gui-run.sh parallel-no-gui 2 3 "$dim" "$itr" >> output"$dim"_"$itr".txt
sh no-gui-run.sh parallel-no-gui 2 4 "$dim" "$itr" >> output"$dim"_"$itr".txt
