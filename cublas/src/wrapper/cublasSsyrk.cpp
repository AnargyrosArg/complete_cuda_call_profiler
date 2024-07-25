#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasSsyrk(char uplo, char trans, int n, int k, float alpha, const float *A, int lda, float beta, float *C, int ldc)
{
	cublasSsyrk(uplo, trans, n, k, alpha, A, lda, beta, C, ldc);
}