#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasSger(int m, int n, float alpha, const float *x, int incx, const float *y, int incy, float *A, int lda)
{
	cublasSger(m, n, alpha, x, incx, y, incy, A, lda);
}