#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasStbmv(char uplo, char trans, char diag, int n, int k, const float *A, int lda, float *x, int incx)
{
	cublasStbmv(uplo, trans, diag, n, k, A, lda, x, incx);
}