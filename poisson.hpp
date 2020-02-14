#ifndef POISSON_H
#define POISSON_H

// Solve Poisson's equation for a rectangular box with Dirichlet
// boundary conditions on each face.
int poisson_dirichlet (double *__restrict__ source, double *__restrict__ potential,
                       unsigned int xsize,  unsigned int ysize, unsigned int zsize,
                       double delta, unsigned int numiters, unsigned int numcores);
                       
void coreSec (unsigned int start,unsigned int stop, int i, int j, int k, double *potential_new,
				int xsize, int ysize, int zsize, double delta, 
				double * __restrict__ source, double *__restrict__ potential, double sixth);


#endif
