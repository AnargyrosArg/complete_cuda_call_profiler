#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
int wrapper_cublasIzamax(int n, const cuDoubleComplex *x, int incx)
{
	int retval = cublasIzamax(n, x, incx);
	return retval;
}