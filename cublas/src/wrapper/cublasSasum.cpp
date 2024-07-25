#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
float wrapper_cublasSasum(int n, const float *x, int incx)
{
	float retval = cublasSasum(n, x, incx);
	return retval;
}