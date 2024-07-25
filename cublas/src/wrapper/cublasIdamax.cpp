#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
int wrapper_cublasIdamax(int n, const double *x, int incx)
{
	int retval = cublasIdamax(n, x, incx);
	return retval;
}