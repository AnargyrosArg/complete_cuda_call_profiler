#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasLtMatmulPreferenceSetAttribute(cublasLtMatmulPreference_t pref, cublasLtMatmulPreferenceAttributes_t attr, const void *buf, size_t sizeInBytes)
{
	cublasStatus_t retval = cublasLtMatmulPreferenceSetAttribute(pref, attr, buf, sizeInBytes);
	return retval;
}