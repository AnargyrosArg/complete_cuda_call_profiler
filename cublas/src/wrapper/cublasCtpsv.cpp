#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasCtpsv(char uplo, char trans, char diag, int n, const cuComplex *AP, cuComplex *x, int incx)
{
	cublasCtpsv(uplo, trans, diag, n, AP, x, incx);
}