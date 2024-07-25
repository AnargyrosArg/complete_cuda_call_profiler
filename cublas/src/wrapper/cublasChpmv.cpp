#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasChpmv(char uplo, int n, cuComplex alpha, const cuComplex *AP, const cuComplex *x, int incx, cuComplex beta, cuComplex *y, int incy)
{
	cublasChpmv(uplo, n, alpha, AP, x, incx, beta, y, incy);
}