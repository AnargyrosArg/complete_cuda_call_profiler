#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasSrotg_v2(cublasHandle_t handle, float *a, float *b, float *c, float *s)
{
	cublasStatus_t retval = cublasSrotg_v2(handle, a, b, c, s);
	return retval;
}