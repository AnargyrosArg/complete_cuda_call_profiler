#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnIRSXgesv_bufferSize(cusolverDnHandle_t handle, cusolverDnIRSParams_t params, cusolver_int_t n, cusolver_int_t nrhs, size_t *lwork_bytes)
{
	cusolverStatus_t retval = cusolverDnIRSXgesv_bufferSize(handle, params, n, nrhs, lwork_bytes);
	return retval;
}