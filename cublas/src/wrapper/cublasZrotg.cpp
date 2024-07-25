#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasZrotg(cuDoubleComplex *ca, cuDoubleComplex cb, double *sc, cuDoubleComplex *cs)
{
	cublasZrotg(ca, cb, sc, cs);
}