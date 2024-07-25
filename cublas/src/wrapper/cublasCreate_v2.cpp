#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
cublasStatus_t (*el_cublas_create_pointer)(cublasHandle_t*) = cublasCreate_v2;

extern "C"
cublasStatus_t wrapper_cublasCreate_v2(cublasHandle_t *handle)
{
	fprintf(stderr,"calling cublasCreate_v2 from wrapper_cublasCreate_v2!\n");
	cublasStatus_t retval = el_cublas_create_pointer(handle);
	return retval;
}