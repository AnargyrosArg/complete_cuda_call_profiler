#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasZaxpy(int n, cuDoubleComplex alpha, const cuDoubleComplex *x, int incx, cuDoubleComplex *y, int incy)
{
	cublasZaxpy(n, alpha, x, incx, y, incy);
}