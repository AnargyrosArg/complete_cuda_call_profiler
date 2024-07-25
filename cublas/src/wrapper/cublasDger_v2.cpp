#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasDger_v2(cublasHandle_t handle, int m, int n, const double *alpha, const double *x, int incx, const double *y, int incy, double *A, int lda)
{
	cublasStatus_t retval = cublasDger_v2(handle, m, n, alpha, x, incx, y, incy, A, lda);
	return retval;
}