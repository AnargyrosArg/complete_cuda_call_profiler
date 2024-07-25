#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasDtrsv(char uplo, char trans, char diag, int n, const double *A, int lda, double *x, int incx)
{
	cublasDtrsv(uplo, trans, diag, n, A, lda, x, incx);
}