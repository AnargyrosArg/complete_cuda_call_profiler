#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnDsyevdx(cusolverDnHandle_t handle, cusolverEigMode_t jobz, cusolverEigRange_t range, cublasFillMode_t uplo, int n, double *A, int lda, double vl, double vu, int il, int iu, int *meig, double *W, double *work, int lwork, int *info)
{
	cusolverStatus_t retval = cusolverDnDsyevdx(handle, jobz, range, uplo, n, A, lda, vl, vu, il, iu, meig, W, work, lwork, info);
	return retval;
}