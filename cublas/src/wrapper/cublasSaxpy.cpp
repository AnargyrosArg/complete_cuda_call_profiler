#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasSaxpy(int n, float alpha, const float *x, int incx, float *y, int incy)
{
	cublasSaxpy(n, alpha, x, incx, y, incy);
}