#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasCsscal(int n, float alpha, cuComplex *x, int incx)
{
	cublasCsscal(n, alpha, x, incx);
}