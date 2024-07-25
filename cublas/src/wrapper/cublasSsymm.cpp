#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasSsymm(char side, char uplo, int m, int n, float alpha, const float *A, int lda, const float *B, int ldb, float beta, float *C, int ldc)
{
	cublasSsymm(side, uplo, m, n, alpha, A, lda, B, ldb, beta, C, ldc);
}