#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
double wrapper_cublasDasum(int n, const double *x, int incx)
{
	double retval = cublasDasum(n, x, incx);
	return retval;
}