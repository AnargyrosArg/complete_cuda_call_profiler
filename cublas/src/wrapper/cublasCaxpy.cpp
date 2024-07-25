#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasCaxpy(int n, cuComplex alpha, const cuComplex *x, int incx, cuComplex *y, int incy)
{
	cublasCaxpy(n, alpha, x, incx, y, incy);
}