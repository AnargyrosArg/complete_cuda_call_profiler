#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasLtMatmulPreferenceCreate)(cublasLtMatmulPreference_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	cublasStatus_t cublasLtMatmulPreferenceCreate(cublasLtMatmulPreference_t *pref){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtMatmulPreferenceCreate)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtMatmulPreferenceCreate = (cublasStatus_t (*)(cublasLtMatmulPreference_t *)) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtMatmulPreferenceCreate");
			fprintf(stderr, "wrapper_cublasLtMatmulPreferenceCreate:%p\n", wrapper_cublasLtMatmulPreferenceCreate);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtMatmulPreferenceCreate():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasLtMatmulPreferenceCreate(pref);
		return retval;
	}
}