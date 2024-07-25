#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasDspr2(char uplo, int n, double alpha, const double *x, int incx, const double *y, int incy, double *AP)
{
	cublasDspr2(uplo, n, alpha, x, incx, y, incy, AP);
}