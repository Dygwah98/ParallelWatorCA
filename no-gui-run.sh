#!/bin/bash

dir="$1"
np="$2"

cd "$dir"
sudo mpicxx -o Wator.out *.cc > /dev/null 2>&1
sudo mpirun -n "$np" ./Wator.out
sudo rm -f Wator.out 
