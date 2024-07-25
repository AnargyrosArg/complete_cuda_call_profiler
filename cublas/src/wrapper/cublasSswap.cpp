#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasSswap(int n, float *x, int incx, float *y, int incy)
{
	cublasSswap(n, x, incx, y, incy);
}