#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnCKgesv_bufferSize(cusolverDnHandle_t handle, cusolver_int_t n, cusolver_int_t nrhs, cuComplex *dA, cusolver_int_t ldda, cusolver_int_t *dipiv, cuComplex *dB, cusolver_int_t lddb, cuComplex *dX, cusolver_int_t lddx, void *dWorkspace, size_t *lwork_bytes)
{
	cusolverStatus_t retval = cusolverDnCKgesv_bufferSize(handle, n, nrhs, dA, ldda, dipiv, dB, lddb, dX, lddx, dWorkspace, lwork_bytes);
	return retval;
}