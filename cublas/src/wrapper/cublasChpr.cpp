#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasChpr(char uplo, int n, float alpha, const cuComplex *x, int incx, cuComplex *AP)
{
	cublasChpr(uplo, n, alpha, x, incx, AP);
}