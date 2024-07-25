#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasSsyr2_v2(cublasHandle_t handle, cublasFillMode_t uplo, int n, const float *alpha, const float *x, int incx, const float *y, int incy, float *A, int lda)
{
	cublasStatus_t retval = cublasSsyr2_v2(handle, uplo, n, alpha, x, incx, y, incy, A, lda);
	return retval;
}