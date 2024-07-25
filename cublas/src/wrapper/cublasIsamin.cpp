#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
int wrapper_cublasIsamin(int n, const float *x, int incx)
{
	int retval = cublasIsamin(n, x, incx);
	return retval;
}