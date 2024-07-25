#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnXgesvdjSetSortEig(gesvdjInfo_t info, int sort_svd)
{
	cusolverStatus_t retval = cusolverDnXgesvdjSetSortEig(info, sort_svd);
	return retval;
}