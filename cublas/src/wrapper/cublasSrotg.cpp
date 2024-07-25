#include <cublas.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasSrotg(float *sa, float *sb, float *sc, float *ss)
{
	cublasSrotg(sa, sb, sc, ss);
}