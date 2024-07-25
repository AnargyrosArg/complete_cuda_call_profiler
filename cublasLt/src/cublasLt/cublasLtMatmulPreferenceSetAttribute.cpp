#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasLtMatmulPreferenceSetAttribute)(cublasLtMatmulPreference_t, cublasLtMatmulPreferenceAttributes_t, const void *, size_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	cublasStatus_t cublasLtMatmulPreferenceSetAttribute(cublasLtMatmulPreference_t pref, cublasLtMatmulPreferenceAttributes_t attr, const void *buf, size_t sizeInBytes) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtMatmulPreferenceSetAttribute)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtMatmulPreferenceSetAttribute = (cublasStatus_t (*)(cublasLtMatmulPreference_t, cublasLtMatmulPreferenceAttributes_t, const void *, size_t)) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtMatmulPreferenceSetAttribute");
			fprintf(stderr, "wrapper_cublasLtMatmulPreferenceSetAttribute:%p\n", wrapper_cublasLtMatmulPreferenceSetAttribute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtMatmulPreferenceSetAttribute():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasLtMatmulPreferenceSetAttribute(pref, attr, buf, sizeInBytes);
		return retval;
	}
}