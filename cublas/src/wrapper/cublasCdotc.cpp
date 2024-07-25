#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cuComplex wrapper_cublasCdotc(int n, const cuComplex *x, int incx, const cuComplex *y, int incy)
{
	cuComplex retval = cublasCdotc(n, x, incx, y, incy);
	return retval;
}