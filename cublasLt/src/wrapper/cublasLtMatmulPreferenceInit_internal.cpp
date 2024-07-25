#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasLtMatmulPreferenceInit_internal(cublasLtMatmulPreference_t pref, size_t size)
{
	cublasStatus_t retval = cublasLtMatmulPreferenceInit_internal(pref, size);
	return retval;
}