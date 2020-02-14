# Cpp-Efficiency

This project aims to implement a numerical algorithm on a desktop computer to make the most efficient use of its caches and multiple cores. 

The algorithm is Jacobi relaxation. This is an iterative algorithm used to approximate differential
equations, for example, Poisson’s and Laplace’s equations. Poisson’s equation can be used to find
the electric potential given a specified charge distribution or temperature given a specified heat
source. There are more efficient ways to solve this problem using Green’s functions and Fourier
transforms but that is not the purpose of this Project.

The algorithm is tested with a single point charge in the centre of a 3 dimensional volume.
The analysis file runs the algorithm 10 times with N = 101, 201, 301, 401, 501, 601, 701, 801, 901.
N being the voxel count for the NxNxN 3 dimensional volume. 

The number of iterations to complete and the number of threads to use are set by the user using command line arguments.
For example after a successful make; './analysis 500 8' will run the analysis using 500 iterations and utilise 8 threads.
The format of the comand line input follows: ./analysis [# of Iterations desired] [# of Threads to use].

The results of the timings are saved to a text file.

