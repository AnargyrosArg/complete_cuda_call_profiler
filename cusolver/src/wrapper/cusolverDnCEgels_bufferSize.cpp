#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnCEgels_bufferSize(cusolverDnHandle_t handle, cusolver_int_t m, cusolver_int_t n, cusolver_int_t nrhs, cuComplex *dA, cusolver_int_t ldda, cuComplex *dB, cusolver_int_t lddb, cuComplex *dX, cusolver_int_t lddx, void *dWorkspace, size_t *lwork_bytes)
{
	cusolverStatus_t retval = cusolverDnCEgels_bufferSize(handle, m, n, nrhs, dA, ldda, dB, lddb, dX, lddx, dWorkspace, lwork_bytes);
	return retval;
}