#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasChpr2(char uplo, int n, cuComplex alpha, const cuComplex *x, int incx, const cuComplex *y, int incy, cuComplex *AP)
{
	cublasChpr2(uplo, n, alpha, x, incx, y, incy, AP);
}