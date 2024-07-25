#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cusolverStatus_t wrapper_cusolverDnCheevdx(cusolverDnHandle_t handle, cusolverEigMode_t jobz, cusolverEigRange_t range, cublasFillMode_t uplo, int n, cuComplex *A, int lda, float vl, float vu, int il, int iu, int *meig, float *W, cuComplex *work, int lwork, int *info)
{
	cusolverStatus_t retval = cusolverDnCheevdx(handle, jobz, range, uplo, n, A, lda, vl, vu, il, iu, meig, W, work, lwork, info);
	return retval;
}