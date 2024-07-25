#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasLtMatmulPreferenceGetAttribute(cublasLtMatmulPreference_t pref, cublasLtMatmulPreferenceAttributes_t attr, void *buf, size_t sizeInBytes, size_t *sizeWritten)
{
	cublasStatus_t retval = cublasLtMatmulPreferenceGetAttribute(pref, attr, buf, sizeInBytes, sizeWritten);
	return retval;
}