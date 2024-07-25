#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasLtMatmulAlgoConfigSetAttribute)(cublasLtMatmulAlgo_t *, cublasLtMatmulAlgoConfigAttributes_t, const void *, size_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	cublasStatus_t cublasLtMatmulAlgoConfigSetAttribute(cublasLtMatmulAlgo_t *algo, cublasLtMatmulAlgoConfigAttributes_t attr, const void *buf, size_t sizeInBytes) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtMatmulAlgoConfigSetAttribute)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtMatmulAlgoConfigSetAttribute = (cublasStatus_t (*)(cublasLtMatmulAlgo_t *, cublasLtMatmulAlgoConfigAttributes_t, const void *, size_t)) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtMatmulAlgoConfigSetAttribute");
			fprintf(stderr, "wrapper_cublasLtMatmulAlgoConfigSetAttribute:%p\n", wrapper_cublasLtMatmulAlgoConfigSetAttribute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtMatmulAlgoConfigSetAttribute():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasLtMatmulAlgoConfigSetAttribute(algo, attr, buf, sizeInBytes);
		return retval;
	}
}