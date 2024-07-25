#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasDtbsv(char uplo, char trans, char diag, int n, int k, const double *A, int lda, double *x, int incx)
{
	cublasDtbsv(uplo, trans, diag, n, k, A, lda, x, incx);
}