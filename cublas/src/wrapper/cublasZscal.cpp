#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasZscal(int n, cuDoubleComplex alpha, cuDoubleComplex *x, int incx)
{
	cublasZscal(n, alpha, x, incx);
}