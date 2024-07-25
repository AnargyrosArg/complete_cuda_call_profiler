#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasDsyr2(char uplo, int n, double alpha, const double *x, int incx, const double *y, int incy, double *A, int lda)
{
	cublasDsyr2(uplo, n, alpha, x, incx, y, incy, A, lda);
}