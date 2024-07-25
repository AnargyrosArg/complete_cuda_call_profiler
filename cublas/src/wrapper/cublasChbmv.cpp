#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasChbmv(char uplo, int n, int k, cuComplex alpha, const cuComplex *A, int lda, const cuComplex *x, int incx, cuComplex beta, cuComplex *y, int incy)
{
	cublasChbmv(uplo, n, k, alpha, A, lda, x, incx, beta, y, incy);
}