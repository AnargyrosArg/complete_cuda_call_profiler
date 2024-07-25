#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasCtpmv(char uplo, char trans, char diag, int n, const cuComplex *AP, cuComplex *x, int incx)
{
	cublasCtpmv(uplo, trans, diag, n, AP, x, incx);
}