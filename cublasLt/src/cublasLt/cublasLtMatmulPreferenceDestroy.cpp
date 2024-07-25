#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasLtMatmulPreferenceDestroy)(cublasLtMatmulPreference_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	cublasStatus_t cublasLtMatmulPreferenceDestroy(cublasLtMatmulPreference_t pref) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtMatmulPreferenceDestroy)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtMatmulPreferenceDestroy = (cublasStatus_t (*)(cublasLtMatmulPreference_t)) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtMatmulPreferenceDestroy");
			fprintf(stderr, "wrapper_cublasLtMatmulPreferenceDestroy:%p\n", wrapper_cublasLtMatmulPreferenceDestroy);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtMatmulPreferenceDestroy():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasLtMatmulPreferenceDestroy(pref);
		return retval;
	}
}