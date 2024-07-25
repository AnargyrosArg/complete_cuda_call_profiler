#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasSrotmg_v2(cublasHandle_t handle, float *d1, float *d2, float *x1, const float *y1, float *param)
{
	cublasStatus_t retval = cublasSrotmg_v2(handle, d1, d2, x1, y1, param);
	return retval;
}