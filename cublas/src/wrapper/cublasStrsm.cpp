#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasStrsm(char side, char uplo, char transa, char diag, int m, int n, float alpha, const float *A, int lda, float *B, int ldb)
{
	cublasStrsm(side, uplo, transa, diag, m, n, alpha, A, lda, B, ldb);
}