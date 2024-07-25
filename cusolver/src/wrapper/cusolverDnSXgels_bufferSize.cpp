#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnSXgels_bufferSize(cusolverDnHandle_t handle, cusolver_int_t m, cusolver_int_t n, cusolver_int_t nrhs, float *dA, cusolver_int_t ldda, float *dB, cusolver_int_t lddb, float *dX, cusolver_int_t lddx, void *dWorkspace, size_t *lwork_bytes)
{
	cusolverStatus_t retval = cusolverDnSXgels_bufferSize(handle, m, n, nrhs, dA, ldda, dB, lddb, dX, lddx, dWorkspace, lwork_bytes);
	return retval;
}