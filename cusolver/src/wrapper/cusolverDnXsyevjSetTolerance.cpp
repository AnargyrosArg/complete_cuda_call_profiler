#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnXsyevjSetTolerance(syevjInfo_t info, double tolerance)
{
	cusolverStatus_t retval = cusolverDnXsyevjSetTolerance(info, tolerance);
	return retval;
}