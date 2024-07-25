#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
double wrapper_cublasDznrm2(int n, const cuDoubleComplex *x, int incx)
{
	double retval = cublasDznrm2(n, x, incx);
	return retval;
}