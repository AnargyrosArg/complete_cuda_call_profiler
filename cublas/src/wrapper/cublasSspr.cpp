#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasSspr(char uplo, int n, float alpha, const float *x, int incx, float *AP)
{
	cublasSspr(uplo, n, alpha, x, incx, AP);
}