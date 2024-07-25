#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasSrotmg(float *sd1, float *sd2, float *sx1, const float *sy1, float *sparam)
{
	cublasSrotmg(sd1, sd2, sx1, sy1, sparam);
}