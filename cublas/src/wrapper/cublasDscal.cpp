#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasDscal(int n, double alpha, double *x, int incx)
{
	cublasDscal(n, alpha, x, incx);
}