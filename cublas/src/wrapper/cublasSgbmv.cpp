#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasSgbmv(char trans, int m, int n, int kl, int ku, float alpha, const float *A, int lda, const float *x, int incx, float beta, float *y, int incy)
{
	cublasSgbmv(trans, m, n, kl, ku, alpha, A, lda, x, incx, beta, y, incy);
}