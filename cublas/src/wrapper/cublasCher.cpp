#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasCher(char uplo, int n, float alpha, const cuComplex *x, int incx, cuComplex *A, int lda)
{
	cublasCher(uplo, n, alpha, x, incx, A, lda);
}