#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasCdgmm(cublasHandle_t handle, cublasSideMode_t mode, int m, int n, const cuComplex *A, int lda, const cuComplex *x, int incx, cuComplex *C, int ldc)
{
	cublasStatus_t retval = cublasCdgmm(handle, mode, m, n, A, lda, x, incx, C, ldc);
	return retval;
}