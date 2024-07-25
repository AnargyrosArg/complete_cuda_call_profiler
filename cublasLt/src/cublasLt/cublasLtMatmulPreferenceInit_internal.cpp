#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasLtMatmulPreferenceInit_internal)(cublasLtMatmulPreference_t, size_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	cublasStatus_t cublasLtMatmulPreferenceInit_internal(cublasLtMatmulPreference_t pref, size_t size) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtMatmulPreferenceInit_internal)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtMatmulPreferenceInit_internal = (cublasStatus_t (*)(cublasLtMatmulPreference_t, size_t)) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtMatmulPreferenceInit_internal");
			fprintf(stderr, "wrapper_cublasLtMatmulPreferenceInit_internal:%p\n", wrapper_cublasLtMatmulPreferenceInit_internal);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtMatmulPreferenceInit_internal():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasLtMatmulPreferenceInit_internal(pref, size);
		return retval;
	}
}