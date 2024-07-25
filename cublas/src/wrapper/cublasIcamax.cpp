#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
int wrapper_cublasIcamax(int n, const cuComplex *x, int incx)
{
	int retval = cublasIcamax(n, x, incx);
	return retval;
}