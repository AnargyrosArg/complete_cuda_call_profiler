#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasZherk(char uplo, char trans, int n, int k, double alpha, const cuDoubleComplex *A, int lda, double beta, cuDoubleComplex *C, int ldc)
{
	cublasZherk(uplo, trans, n, k, alpha, A, lda, beta, C, ldc);
}