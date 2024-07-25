#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasZgemm(char transa, char transb, int m, int n, int k, cuDoubleComplex alpha, const cuDoubleComplex *A, int lda, const cuDoubleComplex *B, int ldb, cuDoubleComplex beta, cuDoubleComplex *C, int ldc)
{
	cublasZgemm(transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc);
}