#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasZcopy(int n, const cuDoubleComplex *x, int incx, cuDoubleComplex *y, int incy)
{
	cublasZcopy(n, x, incx, y, incy);
}