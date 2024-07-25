#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasDrotg_v2(cublasHandle_t handle, double *a, double *b, double *c, double *s)
{
	cublasStatus_t retval = cublasDrotg_v2(handle, a, b, c, s);
	return retval;
}