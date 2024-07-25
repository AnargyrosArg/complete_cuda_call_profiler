#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasCtbsv(char uplo, char trans, char diag, int n, int k, const cuComplex *A, int lda, cuComplex *x, int incx)
{
	cublasCtbsv(uplo, trans, diag, n, k, A, lda, x, incx);
}