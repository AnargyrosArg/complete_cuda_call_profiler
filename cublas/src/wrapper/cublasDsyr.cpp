#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasDsyr(char uplo, int n, double alpha, const double *x, int incx, double *A, int lda)
{
	cublasDsyr(uplo, n, alpha, x, incx, A, lda);
}