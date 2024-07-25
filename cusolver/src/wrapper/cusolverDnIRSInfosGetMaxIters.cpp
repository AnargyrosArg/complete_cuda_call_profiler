#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnIRSInfosGetMaxIters(cusolverDnIRSInfos_t infos, cusolver_int_t *maxiters)
{
	cusolverStatus_t retval = cusolverDnIRSInfosGetMaxIters(infos, maxiters);
	return retval;
}