#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnIRSInfosCreate(cusolverDnIRSInfos_t *infos_ptr)
{
	cusolverStatus_t retval = cusolverDnIRSInfosCreate(infos_ptr);
	return retval;
}