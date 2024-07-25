#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasCrotg_v2(cublasHandle_t handle, cuComplex *a, cuComplex *b, float *c, cuComplex *s)
{
	cublasStatus_t retval = cublasCrotg_v2(handle, a, b, c, s);
	return retval;
}