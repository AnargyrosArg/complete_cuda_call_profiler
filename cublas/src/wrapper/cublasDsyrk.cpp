#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasDsyrk(char uplo, char trans, int n, int k, double alpha, const double *A, int lda, double beta, double *C, int ldc)
{
	cublasDsyrk(uplo, trans, n, k, alpha, A, lda, beta, C, ldc);
}