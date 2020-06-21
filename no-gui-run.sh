#!/bin/bash

dir="$1"
np="$2"
nt="$3"
dim="$4"
iter="$5"

sudo env OMP_DYNAMIC=false > /dev/null
sudo env OMP_NUM_THREADS="$nt" > /dev/null
sudo env OMP_PROC_BIND=close > /dev/null
sudo env OMP_PLACES=core > /dev/null
sudo mpicxx -fopenmp -o Wator.out "$dir"/*.cc #> /dev/null 2>&1
sudo mpiexec -bind-to core -n "$np" ./Wator.out "$dim" "$iter" "$nt"
sudo rm -f Wator.out
