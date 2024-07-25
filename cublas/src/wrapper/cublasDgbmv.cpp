#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasDgbmv(char trans, int m, int n, int kl, int ku, double alpha, const double *A, int lda, const double *x, int incx, double beta, double *y, int incy)
{
	cublasDgbmv(trans, m, n, kl, ku, alpha, A, lda, x, incx, beta, y, incy);
}