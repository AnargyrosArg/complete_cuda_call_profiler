#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnXgesvdjSetTolerance(gesvdjInfo_t info, double tolerance)
{
	cusolverStatus_t retval = cusolverDnXgesvdjSetTolerance(info, tolerance);
	return retval;
}