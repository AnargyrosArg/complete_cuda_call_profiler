#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnIRSParamsSetRefinementSolver(cusolverDnIRSParams_t params, cusolverIRSRefinement_t refinement_solver)
{
	cusolverStatus_t retval = cusolverDnIRSParamsSetRefinementSolver(params, refinement_solver);
	return retval;
}