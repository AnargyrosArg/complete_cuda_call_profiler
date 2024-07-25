#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnIRSInfosGetOuterNiters(cusolverDnIRSInfos_t infos, cusolver_int_t *outer_niters)
{
	cusolverStatus_t retval = cusolverDnIRSInfosGetOuterNiters(infos, outer_niters);
	return retval;
}