#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasSdgmm(cublasHandle_t handle, cublasSideMode_t mode, int m, int n, const float *A, int lda, const float *x, int incx, float *C, int ldc)
{
	cublasStatus_t retval = cublasSdgmm(handle, mode, m, n, A, lda, x, incx, C, ldc);
	return retval;
}