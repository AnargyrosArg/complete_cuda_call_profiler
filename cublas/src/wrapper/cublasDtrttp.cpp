#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasDtrttp(cublasHandle_t handle, cublasFillMode_t uplo, int n, const double *A, int lda, double *AP)
{
	cublasStatus_t retval = cublasDtrttp(handle, uplo, n, A, lda, AP);
	return retval;
}