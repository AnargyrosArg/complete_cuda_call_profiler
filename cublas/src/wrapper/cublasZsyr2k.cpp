#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasZsyr2k(char uplo, char trans, int n, int k, cuDoubleComplex alpha, const cuDoubleComplex *A, int lda, const cuDoubleComplex *B, int ldb, cuDoubleComplex beta, cuDoubleComplex *C, int ldc)
{
	cublasZsyr2k(uplo, trans, n, k, alpha, A, lda, B, ldb, beta, C, ldc);
}