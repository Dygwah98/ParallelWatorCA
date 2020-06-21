# ParallelWatorCA
An hybrid MPI-OpenMP implementation of a cellular automata based on the known Wator model.

## Requirements
OpenMP, MPI, make for the -no-gui versions.

## Build & Run
Just launch the .sh (either gui-run or no-gui-run) as below: <br>
sh .sh [version] [problemDimension] [numberOfProcesses] <br>
Where [numberOfProcesses] is a number >=2 indicating how many processeses will be launched, [problemDimension] is self-explanatory and [version] is one of the following:
<br>
<ul>
<li>serial-no-gui: a single-thread single-process, clean version of the algorithm used (no user interface);
<li>parallel-no-gui: the hybrid MPI-OpenMP implementation of the algorithm (no user interface);
