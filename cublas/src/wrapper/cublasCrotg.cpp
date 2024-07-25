#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasCrotg(cuComplex *ca, cuComplex cb, float *sc, cuComplex *cs)
{
	cublasCrotg(ca, cb, sc, cs);
}