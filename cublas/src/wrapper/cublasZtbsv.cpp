#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasZtbsv(char uplo, char trans, char diag, int n, int k, const cuDoubleComplex *A, int lda, cuDoubleComplex *x, int incx)
{
	cublasZtbsv(uplo, trans, diag, n, k, A, lda, x, incx);
}