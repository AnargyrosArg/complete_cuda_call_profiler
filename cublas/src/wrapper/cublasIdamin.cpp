#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
int wrapper_cublasIdamin(int n, const double *x, int incx)
{
	int retval = cublasIdamin(n, x, incx);
	return retval;
}