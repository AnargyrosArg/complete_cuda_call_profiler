#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasCtrmv(char uplo, char trans, char diag, int n, const cuComplex *A, int lda, cuComplex *x, int incx)
{
	cublasCtrmv(uplo, trans, diag, n, A, lda, x, incx);
}