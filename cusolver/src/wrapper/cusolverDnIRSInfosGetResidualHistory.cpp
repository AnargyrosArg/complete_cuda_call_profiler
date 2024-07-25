#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnIRSInfosGetResidualHistory(cusolverDnIRSInfos_t infos, void **residual_history)
{
	cusolverStatus_t retval = cusolverDnIRSInfosGetResidualHistory(infos, residual_history);
	return retval;
}