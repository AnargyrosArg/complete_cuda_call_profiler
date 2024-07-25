#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cuDoubleComplex wrapper_cublasZdotc(int n, const cuDoubleComplex *x, int incx, const cuDoubleComplex *y, int incy)
{
	cuDoubleComplex retval = cublasZdotc(n, x, incx, y, incy);
	return retval;
}