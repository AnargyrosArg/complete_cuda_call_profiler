#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasDrotmg_v2(cublasHandle_t handle, double *d1, double *d2, double *x1, const double *y1, double *param)
{
	cublasStatus_t retval = cublasDrotmg_v2(handle, d1, d2, x1, y1, param);
	return retval;
}