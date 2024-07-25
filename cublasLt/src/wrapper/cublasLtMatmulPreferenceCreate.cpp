#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasLtMatmulPreferenceCreate(cublasLtMatmulPreference_t *pref)
{
	cublasStatus_t retval = cublasLtMatmulPreferenceCreate(pref);
	return retval;
}