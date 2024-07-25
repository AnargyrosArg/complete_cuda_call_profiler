#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
float wrapper_cublasScnrm2(int n, const cuComplex *x, int incx)
{
	float retval = cublasScnrm2(n, x, incx);
	return retval;
}