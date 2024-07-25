#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasSsbmv(char uplo, int n, int k, float alpha, const float *A, int lda, const float *x, int incx, float beta, float *y, int incy)
{
	cublasSsbmv(uplo, n, k, alpha, A, lda, x, incx, beta, y, incy);
}