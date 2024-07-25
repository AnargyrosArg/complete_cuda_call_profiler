#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasDcopy(int n, const double *x, int incx, double *y, int incy)
{
	cublasDcopy(n, x, incx, y, incy);
}