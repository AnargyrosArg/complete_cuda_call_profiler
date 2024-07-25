#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasCtrsv(char uplo, char trans, char diag, int n, const cuComplex *A, int lda, cuComplex *x, int incx)
{
	cublasCtrsv(uplo, trans, diag, n, A, lda, x, incx);
}