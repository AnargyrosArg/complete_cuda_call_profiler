#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasLtMatmulPreferenceGetAttribute)(cublasLtMatmulPreference_t, cublasLtMatmulPreferenceAttributes_t, void *, size_t, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	cublasStatus_t cublasLtMatmulPreferenceGetAttribute(cublasLtMatmulPreference_t pref, cublasLtMatmulPreferenceAttributes_t attr, void *buf, size_t sizeInBytes, size_t *sizeWritten) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtMatmulPreferenceGetAttribute)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtMatmulPreferenceGetAttribute = (cublasStatus_t (*)(cublasLtMatmulPreference_t, cublasLtMatmulPreferenceAttributes_t, void *, size_t, size_t *)) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtMatmulPreferenceGetAttribute");
			fprintf(stderr, "wrapper_cublasLtMatmulPreferenceGetAttribute:%p\n", wrapper_cublasLtMatmulPreferenceGetAttribute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtMatmulPreferenceGetAttribute():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasLtMatmulPreferenceGetAttribute(pref, attr, buf, sizeInBytes, sizeWritten);
		return retval;
	}
}