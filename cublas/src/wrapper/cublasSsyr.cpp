#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasSsyr(char uplo, int n, float alpha, const float *x, int incx, float *A, int lda)
{
	cublasSsyr(uplo, n, alpha, x, incx, A, lda);
}