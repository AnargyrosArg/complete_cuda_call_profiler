#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasZsymm(char side, char uplo, int m, int n, cuDoubleComplex alpha, const cuDoubleComplex *A, int lda, const cuDoubleComplex *B, int ldb, cuDoubleComplex beta, cuDoubleComplex *C, int ldc)
{
	cublasZsymm(side, uplo, m, n, alpha, A, lda, B, ldb, beta, C, ldc);
}