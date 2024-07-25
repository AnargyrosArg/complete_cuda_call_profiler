#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnIRSXgels_bufferSize(cusolverDnHandle_t handle, cusolverDnIRSParams_t params, cusolver_int_t m, cusolver_int_t n, cusolver_int_t nrhs, size_t *lwork_bytes)
{
	cusolverStatus_t retval = cusolverDnIRSXgels_bufferSize(handle, params, m, n, nrhs, lwork_bytes);
	return retval;
}