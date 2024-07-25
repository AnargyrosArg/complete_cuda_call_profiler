#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasCgemv(char trans, int m, int n, cuComplex alpha, const cuComplex *A, int lda, const cuComplex *x, int incx, cuComplex beta, cuComplex *y, int incy)
{
	cublasCgemv(trans, m, n, alpha, A, lda, x, incx, beta, y, incy);
}