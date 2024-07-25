#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasLtMatmulDescSetAttribute)(cublasLtMatmulDesc_t, cublasLtMatmulDescAttributes_t, const void *, size_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	cublasStatus_t cublasLtMatmulDescSetAttribute(cublasLtMatmulDesc_t matmulDesc, cublasLtMatmulDescAttributes_t attr, const void *buf, size_t sizeInBytes) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtMatmulDescSetAttribute)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtMatmulDescSetAttribute = (cublasStatus_t (*)(cublasLtMatmulDesc_t, cublasLtMatmulDescAttributes_t, const void *, size_t)) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtMatmulDescSetAttribute");
			fprintf(stderr, "wrapper_cublasLtMatmulDescSetAttribute:%p\n", wrapper_cublasLtMatmulDescSetAttribute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtMatmulDescSetAttribute():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasLtMatmulDescSetAttribute(matmulDesc, attr, buf, sizeInBytes);
		return retval;
	}
}