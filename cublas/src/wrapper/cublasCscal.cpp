#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasCscal(int n, cuComplex alpha, cuComplex *x, int incx)
{
	cublasCscal(n, alpha, x, incx);
}