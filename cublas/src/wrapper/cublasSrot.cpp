#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasSrot(int n, float *x, int incx, float *y, int incy, float sc, float ss)
{
	cublasSrot(n, x, incx, y, incy, sc, ss);
}