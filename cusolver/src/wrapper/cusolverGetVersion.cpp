#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverGetVersion(int *version)
{
	cusolverStatus_t retval = cusolverGetVersion(version);
	return retval;
}