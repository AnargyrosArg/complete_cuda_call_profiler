#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasZher2(char uplo, int n, cuDoubleComplex alpha, const cuDoubleComplex *x, int incx, const cuDoubleComplex *y, int incy, cuDoubleComplex *A, int lda)
{
	cublasZher2(uplo, n, alpha, x, incx, y, incy, A, lda);
}