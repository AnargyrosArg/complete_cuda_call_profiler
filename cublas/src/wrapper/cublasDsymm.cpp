#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasDsymm(char side, char uplo, int m, int n, double alpha, const double *A, int lda, const double *B, int ldb, double beta, double *C, int ldc)
{
	cublasDsymm(side, uplo, m, n, alpha, A, lda, B, ldb, beta, C, ldc);
}