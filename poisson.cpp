/// \brief 	Poisson's equation using Jacobi relaxation
/// \author Ronan Fraser 	13819210
/// \author Michael Jopson	86075724
/// \date	Oct 2019

#include <string.h>
#include "poisson.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <thread>

#define INDEX(i,j,k) ((k * (ysize+2)) + j) * (xsize+2) + i
#define v(i,j,k) potential[INDEX(i,j,k)] 
#define f(i,j,k) source[INDEX(i,j,k)] 


/// Solve Poisson's equation for a rectangular box with Dirichlet
/// boundary conditions on each face.
/// \param source is a pointer to a flattened 3-D array for the source function
/// \param potential is a pointer to a flattened 3-D array for the calculated potential
/// \param xsize is the number of elements in the x-direction
/// \param ysize is the number of elements in the y-direction
/// \param zsize is the number of elements in the z-direction
/// \param delta is the voxel spacing in all directions
/// \param numiters is the number of iterations to perform
/// \param numcores is the number of CPU cores to use.  If 0, an optimal number is chosen
/// \return 0 on success.


void coreSec (unsigned int start,unsigned int stop, int i, int j, int k, double *potential_new,
				int xsize, int ysize, int zsize, double delta, 
				double * __restrict__ source, double *__restrict__ potential,double sixth)
{

	for (k = start; k < stop; k++)
	{
		for (j = 1; j < (ysize+2); j++)
		{
			for (i = 1; i < (zsize+2); i++)
			{
				potential_new[INDEX(i, j, k)] = 
				((v(i+1,j,k) + v(i-1,j,k)
				+ v(i,j+1,k) + v(i,j-1,k)
				+ v(i,j,k+1) + v(i,j,(k-1)))
				- (delta * f(i,j,k))) * sixth;  
			} 
		} 
	} 		
}



int poisson_dirichlet (double * __restrict__ source, double *__restrict__ potential,
                       unsigned int xsize,  unsigned int ysize, unsigned int zsize,
                       double delta, unsigned int numiters, unsigned int numcores)
{
	
    const unsigned int size = (xsize+2) * (ysize+2) * (zsize+2);
    int iter, i, j, k;
    
    double *potential_new;
    potential_new = (double *)calloc((xsize+2) * (ysize+2) * (zsize+2), sizeof(*potential_new));
    
    double delta_sq = delta * delta;
    double sixth = 1.0/6.0;
    
    unsigned int c_size = ((xsize + 2) / numcores);
	std::thread th[numcores];

    for (iter = 0; iter < numiters; iter++)
    {
		for (int core = 0; core < numcores; core++)
		{
			th[core] = std::thread (coreSec,(core * c_size),(core * c_size + c_size),i,j,k,potential_new,xsize,ysize,zsize,delta_sq,source,potential,sixth);
		}
		for (int corej = 0; corej < numcores; corej++)
		{
			th[corej].join();
		}
        memcpy(potential, potential_new, size * sizeof(double));
        
    }
    free(potential_new); 
    return 0;
}
