#!/bin/bash

dir="$1"
np="$2"

cd "$dir"/WatorGUI
sudo qmake WatorGUI.pro > /dev/null 2>&1
sudo make -j4 > /dev/null 2>&1
sudo make clean > /dev/null 2>&1
mpirun -n "$np" ./WatorGUI
sudo rm -f WatorGUI
