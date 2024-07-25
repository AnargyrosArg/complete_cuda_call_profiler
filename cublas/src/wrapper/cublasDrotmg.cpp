#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasDrotmg(double *sd1, double *sd2, double *sx1, const double *sy1, double *sparam)
{
	cublasDrotmg(sd1, sd2, sx1, sy1, sparam);
}