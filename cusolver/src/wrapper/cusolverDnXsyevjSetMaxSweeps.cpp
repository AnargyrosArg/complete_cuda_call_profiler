#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnXsyevjSetMaxSweeps(syevjInfo_t info, int max_sweeps)
{
	cusolverStatus_t retval = cusolverDnXsyevjSetMaxSweeps(info, max_sweeps);
	return retval;
}