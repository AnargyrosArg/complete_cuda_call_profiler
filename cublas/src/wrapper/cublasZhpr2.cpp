#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasZhpr2(char uplo, int n, cuDoubleComplex alpha, const cuDoubleComplex *x, int incx, const cuDoubleComplex *y, int incy, cuDoubleComplex *AP)
{
	cublasZhpr2(uplo, n, alpha, x, incx, y, incy, AP);
}