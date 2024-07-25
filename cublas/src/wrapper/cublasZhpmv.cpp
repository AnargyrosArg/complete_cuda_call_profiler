#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasZhpmv(char uplo, int n, cuDoubleComplex alpha, const cuDoubleComplex *AP, const cuDoubleComplex *x, int incx, cuDoubleComplex beta, cuDoubleComplex *y, int incy)
{
	cublasZhpmv(uplo, n, alpha, AP, x, incx, beta, y, incy);
}