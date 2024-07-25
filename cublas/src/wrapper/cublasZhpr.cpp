#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasZhpr(char uplo, int n, double alpha, const cuDoubleComplex *x, int incx, cuDoubleComplex *AP)
{
	cublasZhpr(uplo, n, alpha, x, incx, AP);
}