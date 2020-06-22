# ParallelWatorCA
An hybrid MPI-OpenMP implementation of a cellular automata based on the known Wator model.

## Requirements
OpenMP, MPI, make for the -no-gui versions; same + Allegro5 for the gui version

## Build & Run
Just move to your folder of interest and run the run.sh script file inside as below: <br>
**sh run.sh [MPI_processes] [openMP_threads] [problem_dimension] [iterations_number]** <br>
The following version are available:
<br>
<ul>
<li>**serial-no-gui:** a single-thread single-process, clean version of the algorithm used (no user interface);
<li>**parallel-no-gui:** the hybrid MPI-OpenMP implementation of the algorithm (no user interface);
<li>**parallel-allegro:** simple Allegro graphic output with no interaction; worse performance-wise (only for visual testing).
