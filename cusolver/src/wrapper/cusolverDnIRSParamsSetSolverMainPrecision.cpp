#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnIRSParamsSetSolverMainPrecision(cusolverDnIRSParams_t params, cusolverPrecType_t solver_main_precision)
{
	cusolverStatus_t retval = cusolverDnIRSParamsSetSolverMainPrecision(params, solver_main_precision);
	return retval;
}