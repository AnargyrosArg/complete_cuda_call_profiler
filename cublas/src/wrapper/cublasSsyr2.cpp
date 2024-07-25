#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasSsyr2(char uplo, int n, float alpha, const float *x, int incx, const float *y, int incy, float *A, int lda)
{
	cublasSsyr2(uplo, n, alpha, x, incx, y, incy, A, lda);
}