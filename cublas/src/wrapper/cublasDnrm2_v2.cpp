#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasDnrm2_v2(cublasHandle_t handle, int n, const double *x, int incx, double *result)
{
	cublasStatus_t retval = cublasDnrm2_v2(handle, n, x, incx, result);
	return retval;
}