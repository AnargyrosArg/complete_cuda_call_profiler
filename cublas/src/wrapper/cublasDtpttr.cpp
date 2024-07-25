#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasDtpttr(cublasHandle_t handle, cublasFillMode_t uplo, int n, const double *AP, double *A, int lda)
{
	cublasStatus_t retval = cublasDtpttr(handle, uplo, n, AP, A, lda);
	return retval;
}