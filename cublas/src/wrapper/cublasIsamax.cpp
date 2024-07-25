#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
int wrapper_cublasIsamax(int n, const float *x, int incx)
{
	int retval = cublasIsamax(n, x, incx);
	return retval;
}