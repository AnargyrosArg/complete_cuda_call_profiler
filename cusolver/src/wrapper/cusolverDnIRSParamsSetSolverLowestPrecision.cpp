#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnIRSParamsSetSolverLowestPrecision(cusolverDnIRSParams_t params, cusolverPrecType_t solver_lowest_precision)
{
	cusolverStatus_t retval = cusolverDnIRSParamsSetSolverLowestPrecision(params, solver_lowest_precision);
	return retval;
}