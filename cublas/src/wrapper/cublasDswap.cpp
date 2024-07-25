#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasDswap(int n, double *x, int incx, double *y, int incy)
{
	cublasDswap(n, x, incx, y, incy);
}