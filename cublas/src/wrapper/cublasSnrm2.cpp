#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
float wrapper_cublasSnrm2(int n, const float *x, int incx)
{
	float retval = cublasSnrm2(n, x, incx);
	return retval;
}