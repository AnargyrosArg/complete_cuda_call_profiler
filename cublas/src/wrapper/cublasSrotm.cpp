#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasSrotm(int n, float *x, int incx, float *y, int incy, const float *sparam)
{
	cublasSrotm(n, x, incx, y, incy, sparam);
}