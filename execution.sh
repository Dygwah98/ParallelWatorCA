#!/bin/bash

dir="$1"
np="$2"

cd "$dir"/WatorGUI
sudo qmake WatorGUI.pro > /dev/null
sudo make -j4 > /dev/null
sudo make clean > /dev/null
mpirun -n "$np" ./WatorGUI
sudo rm -f WatorGUI
