#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasScopy(int n, const float *x, int incx, float *y, int incy)
{
	cublasScopy(n, x, incx, y, incy);
}