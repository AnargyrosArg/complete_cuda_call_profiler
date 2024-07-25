#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasDaxpy(int n, double alpha, const double *x, int incx, double *y, int incy)
{
	cublasDaxpy(n, alpha, x, incx, y, incy);
}