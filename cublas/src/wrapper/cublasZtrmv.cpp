#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasZtrmv(char uplo, char trans, char diag, int n, const cuDoubleComplex *A, int lda, cuDoubleComplex *x, int incx)
{
	cublasZtrmv(uplo, trans, diag, n, A, lda, x, incx);
}