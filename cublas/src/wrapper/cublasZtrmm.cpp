#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasZtrmm(char side, char uplo, char transa, char diag, int m, int n, cuDoubleComplex alpha, const cuDoubleComplex *A, int lda, cuDoubleComplex *B, int ldb)
{
	cublasZtrmm(side, uplo, transa, diag, m, n, alpha, A, lda, B, ldb);
}