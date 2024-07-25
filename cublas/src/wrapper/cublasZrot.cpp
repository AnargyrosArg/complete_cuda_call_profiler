#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasZrot(int n, cuDoubleComplex *x, int incx, cuDoubleComplex *y, int incy, double sc, cuDoubleComplex cs)
{
	cublasZrot(n, x, incx, y, incy, sc, cs);
}