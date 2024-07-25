#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
int wrapper_cublasIcamin(int n, const cuComplex *x, int incx)
{
	int retval = cublasIcamin(n, x, incx);
	return retval;
}