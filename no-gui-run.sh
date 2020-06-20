#!/bin/bash

dir="$1"
np="$2"
nt="$3"
dim="$4"
iter="$5"

sudo mpicxx -fopenmp -o Wator.out "$dir"/*.cc #> /dev/null 2>&1
sudo mpirun -n "$np" ./Wator.out "$dim" "$iter" "$nt"
sudo rm -f Wator.out
