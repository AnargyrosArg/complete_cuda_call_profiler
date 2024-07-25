#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
float wrapper_cublasSdot(int n, const float *x, int incx, const float *y, int incy)
{
	float retval = cublasSdot(n, x, incx, y, incy);
	return retval;
}