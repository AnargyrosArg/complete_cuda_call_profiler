#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasDsyr2k(char uplo, char trans, int n, int k, double alpha, const double *A, int lda, const double *B, int ldb, double beta, double *C, int ldc)
{
	cublasDsyr2k(uplo, trans, n, k, alpha, A, lda, B, ldb, beta, C, ldc);
}