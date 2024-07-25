#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasZgbmv(char trans, int m, int n, int kl, int ku, cuDoubleComplex alpha, const cuDoubleComplex *A, int lda, const cuDoubleComplex *x, int incx, cuDoubleComplex beta, cuDoubleComplex *y, int incy)
{
	cublasZgbmv(trans, m, n, kl, ku, alpha, A, lda, x, incx, beta, y, incy);
}