#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasLtMatmulAlgoConfigGetAttribute)(const cublasLtMatmulAlgo_t *, cublasLtMatmulAlgoConfigAttributes_t, void *, size_t, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	cublasStatus_t cublasLtMatmulAlgoConfigGetAttribute(const cublasLtMatmulAlgo_t *algo, cublasLtMatmulAlgoConfigAttributes_t attr, void *buf, size_t sizeInBytes, size_t *sizeWritten){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtMatmulAlgoConfigGetAttribute)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtMatmulAlgoConfigGetAttribute = (cublasStatus_t (*)(const cublasLtMatmulAlgo_t *, cublasLtMatmulAlgoConfigAttributes_t, void *, size_t, size_t *)) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtMatmulAlgoConfigGetAttribute");
			fprintf(stderr, "wrapper_cublasLtMatmulAlgoConfigGetAttribute:%p\n", wrapper_cublasLtMatmulAlgoConfigGetAttribute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtMatmulAlgoConfigGetAttribute():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasLtMatmulAlgoConfigGetAttribute(algo, attr, buf, sizeInBytes, sizeWritten);
		return retval;
	}
}