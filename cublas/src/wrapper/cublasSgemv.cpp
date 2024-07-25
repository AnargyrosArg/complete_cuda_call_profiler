#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasSgemv(char trans, int m, int n, float alpha, const float *A, int lda, const float *x, int incx, float beta, float *y, int incy)
{
	cublasSgemv(trans, m, n, alpha, A, lda, x, incx, beta, y, incy);
}