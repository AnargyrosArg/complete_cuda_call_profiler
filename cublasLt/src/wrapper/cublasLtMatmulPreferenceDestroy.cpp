#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasLtMatmulPreferenceDestroy(cublasLtMatmulPreference_t pref)
{
	cublasStatus_t retval = cublasLtMatmulPreferenceDestroy(pref);
	return retval;
}