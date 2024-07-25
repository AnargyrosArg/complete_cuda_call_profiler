#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasZgemv(char trans, int m, int n, cuDoubleComplex alpha, const cuDoubleComplex *A, int lda, const cuDoubleComplex *x, int incx, cuDoubleComplex beta, cuDoubleComplex *y, int incy)
{
	cublasZgemv(trans, m, n, alpha, A, lda, x, incx, beta, y, incy);
}