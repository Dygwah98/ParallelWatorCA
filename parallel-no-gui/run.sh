#!/bin/bash

np="$1"
nt="$2"
dim="$3"
iter="$4"

sudo env OMP_DYNAMIC=false > /dev/null
sudo env OMP_NUM_THREADS="$nt" > /dev/null
sudo env OMP_PROC_BIND=master > /dev/null
sudo env OMP_PLACES=core > /dev/null
sudo mpicxx -fopenmp -o Wator.out *.cc #> /dev/null 2>&1
sudo nice -n -20 mpiexec --bind-to core -n "$np" nice -n -20 ./Wator.out "$dim" "$iter" "$nt"
sudo rm -f Wator.out
