#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnXsyevjSetSortEig(syevjInfo_t info, int sort_eig)
{
	cusolverStatus_t retval = cusolverDnXsyevjSetSortEig(info, sort_eig);
	return retval;
}