#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasSspmv(char uplo, int n, float alpha, const float *AP, const float *x, int incx, float beta, float *y, int incy)
{
	cublasSspmv(uplo, n, alpha, AP, x, incx, beta, y, incy);
}