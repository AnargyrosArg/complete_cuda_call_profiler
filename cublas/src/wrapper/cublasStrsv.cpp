#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasStrsv(char uplo, char trans, char diag, int n, const float *A, int lda, float *x, int incx)
{
	cublasStrsv(uplo, trans, diag, n, A, lda, x, incx);
}