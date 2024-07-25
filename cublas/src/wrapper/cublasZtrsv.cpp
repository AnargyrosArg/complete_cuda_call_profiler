#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasZtrsv(char uplo, char trans, char diag, int n, const cuDoubleComplex *A, int lda, cuDoubleComplex *x, int incx)
{
	cublasZtrsv(uplo, trans, diag, n, A, lda, x, incx);
}