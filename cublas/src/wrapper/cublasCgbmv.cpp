#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasCgbmv(char trans, int m, int n, int kl, int ku, cuComplex alpha, const cuComplex *A, int lda, const cuComplex *x, int incx, cuComplex beta, cuComplex *y, int incy)
{
	cublasCgbmv(trans, m, n, kl, ku, alpha, A, lda, x, incx, beta, y, incy);
}