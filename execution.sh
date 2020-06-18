#!/bin/bash

dir="$1"
np="$2"

cd "$dir"/WatorGUI
sudo qmake WatorGUI.pro
sudo make -j4
sudo make clean
mpirun -n "$np" ./WatorGUI
sudo rm -f WatorGUI
