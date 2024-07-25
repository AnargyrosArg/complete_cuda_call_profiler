#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasZher(char uplo, int n, double alpha, const cuDoubleComplex *x, int incx, cuDoubleComplex *A, int lda)
{
	cublasZher(uplo, n, alpha, x, incx, A, lda);
}