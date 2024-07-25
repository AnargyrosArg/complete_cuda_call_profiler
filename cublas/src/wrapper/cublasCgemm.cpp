#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasCgemm(char transa, char transb, int m, int n, int k, cuComplex alpha, const cuComplex *A, int lda, const cuComplex *B, int ldb, cuComplex beta, cuComplex *C, int ldc)
{
	cublasCgemm(transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc);
}