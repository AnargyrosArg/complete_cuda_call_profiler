#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasZswap(int n, cuDoubleComplex *x, int incx, cuDoubleComplex *y, int incy)
{
	cublasZswap(n, x, incx, y, incy);
}