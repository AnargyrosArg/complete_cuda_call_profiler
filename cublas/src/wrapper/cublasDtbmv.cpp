#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasDtbmv(char uplo, char trans, char diag, int n, int k, const double *A, int lda, double *x, int incx)
{
	cublasDtbmv(uplo, trans, diag, n, k, A, lda, x, incx);
}