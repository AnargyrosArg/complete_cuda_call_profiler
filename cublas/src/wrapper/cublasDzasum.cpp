#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
double wrapper_cublasDzasum(int n, const cuDoubleComplex *x, int incx)
{
	double retval = cublasDzasum(n, x, incx);
	return retval;
}