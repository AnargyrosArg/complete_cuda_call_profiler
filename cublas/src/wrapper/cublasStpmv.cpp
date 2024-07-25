#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasStpmv(char uplo, char trans, char diag, int n, const float *AP, float *x, int incx)
{
	cublasStpmv(uplo, trans, diag, n, AP, x, incx);
}