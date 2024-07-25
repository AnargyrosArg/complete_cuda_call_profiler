#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasCrot(int n, cuComplex *x, int incx, cuComplex *y, int incy, float c, cuComplex s)
{
	cublasCrot(n, x, incx, y, incy, c, s);
}