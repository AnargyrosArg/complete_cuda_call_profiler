#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnDXgels(cusolverDnHandle_t handle, cusolver_int_t m, cusolver_int_t n, cusolver_int_t nrhs, double *dA, cusolver_int_t ldda, double *dB, cusolver_int_t lddb, double *dX, cusolver_int_t lddx, void *dWorkspace, size_t lwork_bytes, cusolver_int_t *iter, cusolver_int_t *d_info)
{
	cusolverStatus_t retval = cusolverDnDXgels(handle, m, n, nrhs, dA, ldda, dB, lddb, dX, lddx, dWorkspace, lwork_bytes, iter, d_info);
	return retval;
}