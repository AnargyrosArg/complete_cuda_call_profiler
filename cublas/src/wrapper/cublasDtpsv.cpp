#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasDtpsv(char uplo, char trans, char diag, int n, const double *AP, double *x, int incx)
{
	cublasDtpsv(uplo, trans, diag, n, AP, x, incx);
}