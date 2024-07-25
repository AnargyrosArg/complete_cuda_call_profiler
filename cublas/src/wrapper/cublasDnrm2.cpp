#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
double wrapper_cublasDnrm2(int n, const double *x, int incx)
{
	double retval = cublasDnrm2(n, x, incx);
	return retval;
}