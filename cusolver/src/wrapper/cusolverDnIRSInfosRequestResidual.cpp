#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnIRSInfosRequestResidual(cusolverDnIRSInfos_t infos)
{
	cusolverStatus_t retval = cusolverDnIRSInfosRequestResidual(infos);
	return retval;
}