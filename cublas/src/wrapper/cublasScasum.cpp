#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
float wrapper_cublasScasum(int n, const cuComplex *x, int incx)
{
	float retval = cublasScasum(n, x, incx);
	return retval;
}