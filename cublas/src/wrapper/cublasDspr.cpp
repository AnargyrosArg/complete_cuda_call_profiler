#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasDspr(char uplo, int n, double alpha, const double *x, int incx, double *AP)
{
	cublasDspr(uplo, n, alpha, x, incx, AP);
}