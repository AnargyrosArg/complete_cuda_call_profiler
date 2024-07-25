#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasDrotg(double *sa, double *sb, double *sc, double *ss)
{
	cublasDrotg(sa, sb, sc, ss);
}