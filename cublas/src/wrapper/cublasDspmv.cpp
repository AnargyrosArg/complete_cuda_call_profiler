#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasDspmv(char uplo, int n, double alpha, const double *AP, const double *x, int incx, double beta, double *y, int incy)
{
	cublasDspmv(uplo, n, alpha, AP, x, incx, beta, y, incy);
}