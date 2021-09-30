#ifndef CNTR_GLOBAL_SETTINGS_H
#define CNTR_GLOBAL_SETTINGS_H

/////////////////////////////////////////////////////////////////////
// determine whether OpenMP routines are available
// requires compilation with -fopenmp

#ifdef CNTR_USE_OMP
#undef CNTR_USE_OMP
#define CNTR_USE_OMP 1
#endif

#if CNTR_USE_OMP==1
#include <omp.h>
#endif


/////////////////////////////////////////////////////////////////////
// determine whether MPI routines are available
// (this includes, e.g., some member functions for date exchange etc.)

#ifdef CNTR_USE_MPI
#undef CNTR_USE_MPI
#define CNTR_USE_MPI 1
#endif

#define MPI_MASTER 0
#if CNTR_USE_MPI==1
#include <mpi.h>
#endif

#ifdef CNTR_USE_HDF5
#include "hdf5/hdf5_interface.hpp"
#endif


#define MAX_SOLVE_ORDER 5

#define CNTR_PI 3.14159265358979323846

#define CNTR_MAT_FOURIER 0
#define CNTR_MAT_CG 1
#define CNTR_MAT_FIXPOINT 2

#define GREEN cntr::herm_matrix<double>
#define GREEN_TSTP cntr::herm_matrix_timestep<double>
#define CFUNC cntr::function<double>
#define CINTEG integration::I<double>
#define II cdouble(0.0,1.0)

#define FERMION -1
#define BOSON 1

#include <cmath>
#include <cassert>
#include <iostream>
#include <fstream>
#include <complex>
#include <vector>
#include <string>
#include "string.h"

// using eigen library
#include "eigen_typedef.h"
#include <unsupported/Eigen/MatrixFunctions>


// global types
typedef double r_type;
typedef std::complex<double> cdouble;

#endif // CNTR_GLOBAL_SETTINGS_H
