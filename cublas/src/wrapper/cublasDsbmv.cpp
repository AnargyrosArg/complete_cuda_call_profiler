#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasDsbmv(char uplo, int n, int k, double alpha, const double *A, int lda, const double *x, int incx, double beta, double *y, int incy)
{
	cublasDsbmv(uplo, n, k, alpha, A, lda, x, incx, beta, y, incy);
}