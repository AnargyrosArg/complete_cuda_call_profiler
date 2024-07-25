#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasDdgmm(cublasHandle_t handle, cublasSideMode_t mode, int m, int n, const double *A, int lda, const double *x, int incx, double *C, int ldc)
{
	cublasStatus_t retval = cublasDdgmm(handle, mode, m, n, A, lda, x, incx, C, ldc);
	return retval;
}