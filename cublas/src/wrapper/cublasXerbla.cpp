#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
void wrapper_cublasXerbla(const char *srName, int info)
{
	cublasXerbla(srName, info);
}