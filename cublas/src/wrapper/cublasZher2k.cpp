#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasZher2k(char uplo, char trans, int n, int k, cuDoubleComplex alpha, const cuDoubleComplex *A, int lda, const cuDoubleComplex *B, int ldb, double beta, cuDoubleComplex *C, int ldc)
{
	cublasZher2k(uplo, trans, n, k, alpha, A, lda, B, ldb, beta, C, ldc);
}