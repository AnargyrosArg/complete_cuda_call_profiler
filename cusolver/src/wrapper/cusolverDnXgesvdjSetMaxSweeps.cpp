#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnXgesvdjSetMaxSweeps(gesvdjInfo_t info, int max_sweeps)
{
	cusolverStatus_t retval = cusolverDnXgesvdjSetMaxSweeps(info, max_sweeps);
	return retval;
}