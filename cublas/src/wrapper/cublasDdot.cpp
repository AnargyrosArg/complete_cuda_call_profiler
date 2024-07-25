#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
double wrapper_cublasDdot(int n, const double *x, int incx, const double *y, int incy)
{
	double retval = cublasDdot(n, x, incx, y, incy);
	return retval;
}