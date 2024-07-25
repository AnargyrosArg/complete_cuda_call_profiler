#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasSsyr2k(char uplo, char trans, int n, int k, float alpha, const float *A, int lda, const float *B, int ldb, float beta, float *C, int ldc)
{
	cublasSsyr2k(uplo, trans, n, k, alpha, A, lda, B, ldb, beta, C, ldc);
}