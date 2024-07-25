#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cuDoubleComplex wrapper_cublasZdotu(int n, const cuDoubleComplex *x, int incx, const cuDoubleComplex *y, int incy)
{
	cuDoubleComplex retval = cublasZdotu(n, x, incx, y, incy);
	return retval;
}