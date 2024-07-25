#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasDger(int m, int n, double alpha, const double *x, int incx, const double *y, int incy, double *A, int lda)
{
	cublasDger(m, n, alpha, x, incx, y, incy, A, lda);
}