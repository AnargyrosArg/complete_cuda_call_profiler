#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasCgerc(int m, int n, cuComplex alpha, const cuComplex *x, int incx, const cuComplex *y, int incy, cuComplex *A, int lda)
{
	cublasCgerc(m, n, alpha, x, incx, y, incy, A, lda);
}