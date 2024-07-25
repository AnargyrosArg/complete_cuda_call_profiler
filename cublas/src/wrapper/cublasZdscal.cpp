#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasZdscal(int n, double alpha, cuDoubleComplex *x, int incx)
{
	cublasZdscal(n, alpha, x, incx);
}