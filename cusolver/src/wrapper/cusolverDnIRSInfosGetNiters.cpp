#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnIRSInfosGetNiters(cusolverDnIRSInfos_t infos, cusolver_int_t *niters)
{
	cusolverStatus_t retval = cusolverDnIRSInfosGetNiters(infos, niters);
	return retval;
}