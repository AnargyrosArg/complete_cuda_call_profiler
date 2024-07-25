#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasSscal(int n, float alpha, float *x, int incx)
{
	cublasSscal(n, alpha, x, incx);
}