#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasZtpttr(cublasHandle_t handle, cublasFillMode_t uplo, int n, const cuDoubleComplex *AP, cuDoubleComplex *A, int lda)
{
	cublasStatus_t retval = cublasZtpttr(handle, uplo, n, AP, A, lda);
	return retval;
}