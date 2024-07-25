#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasDrot(int n, double *x, int incx, double *y, int incy, double sc, double ss)
{
	cublasDrot(n, x, incx, y, incy, sc, ss);
}