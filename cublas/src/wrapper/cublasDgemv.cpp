#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasDgemv(char trans, int m, int n, double alpha, const double *A, int lda, const double *x, int incx, double beta, double *y, int incy)
{
	cublasDgemv(trans, m, n, alpha, A, lda, x, incx, beta, y, incy);
}