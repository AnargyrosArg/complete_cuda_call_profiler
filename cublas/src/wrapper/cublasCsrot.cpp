#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasCsrot(int n, cuComplex *x, int incx, cuComplex *y, int incy, float c, float s)
{
	cublasCsrot(n, x, incx, y, incy, c, s);
}