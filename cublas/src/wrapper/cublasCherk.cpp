#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasCherk(char uplo, char trans, int n, int k, float alpha, const cuComplex *A, int lda, float beta, cuComplex *C, int ldc)
{
	cublasCherk(uplo, trans, n, k, alpha, A, lda, beta, C, ldc);
}