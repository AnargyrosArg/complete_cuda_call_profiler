#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasCsymm(char side, char uplo, int m, int n, cuComplex alpha, const cuComplex *A, int lda, const cuComplex *B, int ldb, cuComplex beta, cuComplex *C, int ldc)
{
	cublasCsymm(side, uplo, m, n, alpha, A, lda, B, ldb, beta, C, ldc);
}