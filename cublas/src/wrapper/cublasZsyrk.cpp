#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasZsyrk(char uplo, char trans, int n, int k, cuDoubleComplex alpha, const cuDoubleComplex *A, int lda, cuDoubleComplex beta, cuDoubleComplex *C, int ldc)
{
	cublasZsyrk(uplo, trans, n, k, alpha, A, lda, beta, C, ldc);
}