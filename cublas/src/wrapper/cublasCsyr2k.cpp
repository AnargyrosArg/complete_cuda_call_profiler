#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasCsyr2k(char uplo, char trans, int n, int k, cuComplex alpha, const cuComplex *A, int lda, const cuComplex *B, int ldb, cuComplex beta, cuComplex *C, int ldc)
{
	cublasCsyr2k(uplo, trans, n, k, alpha, A, lda, B, ldb, beta, C, ldc);
}