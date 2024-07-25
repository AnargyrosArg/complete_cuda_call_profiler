#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasCcopy(int n, const cuComplex *x, int incx, cuComplex *y, int incy)
{
	cublasCcopy(n, x, incx, y, incy);
}