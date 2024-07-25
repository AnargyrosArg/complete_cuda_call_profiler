#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnIRSParamsSetSolverPrecisions(cusolverDnIRSParams_t params, cusolverPrecType_t solver_main_precision, cusolverPrecType_t solver_lowest_precision)
{
	cusolverStatus_t retval = cusolverDnIRSParamsSetSolverPrecisions(params, solver_main_precision, solver_lowest_precision);
	return retval;
}