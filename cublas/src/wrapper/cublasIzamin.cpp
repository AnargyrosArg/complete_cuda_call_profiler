#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
int wrapper_cublasIzamin(int n, const cuDoubleComplex *x, int incx)
{
	int retval = cublasIzamin(n, x, incx);
	return retval;
}