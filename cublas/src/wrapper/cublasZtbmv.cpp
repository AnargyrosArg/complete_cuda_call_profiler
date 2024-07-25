#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasZtbmv(char uplo, char trans, char diag, int n, int k, const cuDoubleComplex *A, int lda, cuDoubleComplex *x, int incx)
{
	cublasZtbmv(uplo, trans, diag, n, k, A, lda, x, incx);
}