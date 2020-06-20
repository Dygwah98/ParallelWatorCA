# ParallelWatorCA
An hybrid MPI-OpenMP implementation of a cellular automata based on the known Wator model.

# Requirements
OpenMP, MPI, make for the -no-gui versions; Qt5+ and qmake for the others.

# Build & Run
Just launch the .sh (either gui-run or no-gui-run) as below: <br>
sh .sh [version] [problemDimension] [numberOfProcesses] <br>
Where [numberOfProcesses] is a number >=2 indicating how many processeses will be launched, [problemDimension] is self-explanatory nad [version] is one of the following:
<br>
<ul>
<li><b>serial-no-gui: a single-thread single-process, clean version of the algorithm used (no user interface);
<li><b>parallel-no-gui: the hybrid MPI-OpenMP implementation of the algorithm (no user interface);
<li><b>parallel: still WIP 
<li><b>serial: still WIP 
