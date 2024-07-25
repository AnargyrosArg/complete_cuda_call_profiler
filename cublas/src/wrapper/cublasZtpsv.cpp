#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasZtpsv(char uplo, char trans, char diag, int n, const cuDoubleComplex *AP, cuDoubleComplex *x, int incx)
{
	cublasZtpsv(uplo, trans, diag, n, AP, x, incx);
}