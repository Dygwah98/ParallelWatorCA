#!/bin/bash

dir="$1"
np="$2"
dim="$3"
iter="$4"

sudo mpicxx -o Wator.out "$dir"/*.cc #> /dev/null 2>&1
sudo mpirun -n "$np" ./Wator.out "$dim" "$iter"
sudo rm -f Wator.out
