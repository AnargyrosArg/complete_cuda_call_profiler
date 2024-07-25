#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnSXgesv(cusolverDnHandle_t handle, cusolver_int_t n, cusolver_int_t nrhs, float *dA, cusolver_int_t ldda, cusolver_int_t *dipiv, float *dB, cusolver_int_t lddb, float *dX, cusolver_int_t lddx, void *dWorkspace, size_t lwork_bytes, cusolver_int_t *iter, cusolver_int_t *d_info)
{
	cusolverStatus_t retval = cusolverDnSXgesv(handle, n, nrhs, dA, ldda, dipiv, dB, lddb, dX, lddx, dWorkspace, lwork_bytes, iter, d_info);
	return retval;
}