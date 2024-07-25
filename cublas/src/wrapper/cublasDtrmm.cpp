#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasDtrmm(char side, char uplo, char transa, char diag, int m, int n, double alpha, const double *A, int lda, double *B, int ldb)
{
	cublasDtrmm(side, uplo, transa, diag, m, n, alpha, A, lda, B, ldb);
}