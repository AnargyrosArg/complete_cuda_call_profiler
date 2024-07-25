#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasCher2k(char uplo, char trans, int n, int k, cuComplex alpha, const cuComplex *A, int lda, const cuComplex *B, int ldb, float beta, cuComplex *C, int ldc)
{
	cublasCher2k(uplo, trans, n, k, alpha, A, lda, B, ldb, beta, C, ldc);
}