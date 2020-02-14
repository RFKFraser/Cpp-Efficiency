/// \brief 	Analysis program for solving Poisson's 
///			equation across variable and saving output to txt file
/// \author Ronan Fraser 	13819210
/// \author Michael Jopson	86075724
/// \date	Oct 2019

#include <stdlib.h>
#include <stdio.h>
#include "poisson.hpp"
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono; 

int main (int argc, char *argv[])
{
	
    double *source;
    double *potential;
    unsigned int N;
    unsigned int i;
    unsigned int numiters;
    unsigned int numcores;    
    unsigned int xsize;
    unsigned int ysize;
    unsigned int zsize;    
    double delta = 0.1;

    if (argc < 2)
    {
        fprintf (stderr, "Usage: %s sized numiters\n", argv[0]);
        return 1;
    }
    
    numiters = atoi(argv[1]);
	numcores = atoi(argv[2]);
	
	/* open the file*/
	FILE *f = fopen("Analysis.txt", "a");
	if (f == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}
	/* writes to file*/ 
	fprintf(f, "--- Inefficent Unpacking ---\n");
	/* close the file*/ 
	fclose(f);
    
    for(N = 101; N < 800; N += 100){
    //for(numcores = 1; numcores < 9; numcores = numcores + 1){
		
		/* open the file*/ 
		FILE *f = fopen("Analysis.txt", "a");
		if (f == NULL)
		{
			printf("Error opening file!\n");
			exit(1);
		}
		
		//N = 301;
		xsize = N;
		ysize = N;
		zsize = N;
		
		//fprintf(stderr,"Pre memory allocation \n");
		source = (double *)calloc((xsize+2) * (ysize+2) * (zsize+2), sizeof(*source));
		potential = (double *)calloc((xsize+2) * (ysize+2) * (zsize+2), sizeof(*potential));
		//fprintf(stderr,"setting middle = 1 \n");
		
		source[(((zsize+2) / 2 * (ysize+2)) + (ysize+2) / 2) * (xsize+2) + (xsize+2) / 2] = 1.0;   

		for (i = 0; i < 10; i++){
			

			source = (double *)calloc((xsize+2) * (ysize+2) * (zsize+2), sizeof(*source));
			potential = (double *)calloc((xsize+2) * (ysize+2) * (zsize+2), sizeof(*potential));
			source[(((zsize+2) / 2 * (ysize+2)) + (ysize+2) / 2) * (xsize+2) + (xsize+2) / 2] = 1.0;  			
			
			
			// Function
			auto start = high_resolution_clock::now();  
			poisson_dirichlet(source, potential, xsize, ysize, zsize, delta,
							  numiters, numcores);
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start); 
			float time_s = (duration.count())/1000000.0;
			
			printf("(N = %i, i = %i) Function executed in %f Seconds\n", N, i, time_s);
		          
			/* writes to file*/ 
			fprintf(f, "%d, %f\n", N, time_s);   
			
			free(source);
			free(potential);

		}
		/* close the file*/ 
		fclose(f);

	}
    
    return 0;
}
