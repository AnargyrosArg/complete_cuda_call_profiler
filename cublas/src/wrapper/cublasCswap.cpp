#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasCswap(int n, cuComplex *x, int incx, cuComplex *y, int incy)
{
	cublasCswap(n, x, incx, y, incy);
}