#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasZdrot(int n, cuDoubleComplex *x, int incx, cuDoubleComplex *y, int incy, double c, double s)
{
	cublasZdrot(n, x, incx, y, incy, c, s);
}