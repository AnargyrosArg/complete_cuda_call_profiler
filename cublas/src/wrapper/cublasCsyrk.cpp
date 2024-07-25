#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasCsyrk(char uplo, char trans, int n, int k, cuComplex alpha, const cuComplex *A, int lda, cuComplex beta, cuComplex *C, int ldc)
{
	cublasCsyrk(uplo, trans, n, k, alpha, A, lda, beta, C, ldc);
}