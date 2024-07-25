#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasDrotm(int n, double *x, int incx, double *y, int incy, const double *sparam)
{
	cublasDrotm(n, x, incx, y, incy, sparam);
}