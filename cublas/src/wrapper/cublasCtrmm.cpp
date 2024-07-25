#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasCtrmm(char side, char uplo, char transa, char diag, int m, int n, cuComplex alpha, const cuComplex *A, int lda, cuComplex *B, int ldb)
{
	cublasCtrmm(side, uplo, transa, diag, m, n, alpha, A, lda, B, ldb);
}