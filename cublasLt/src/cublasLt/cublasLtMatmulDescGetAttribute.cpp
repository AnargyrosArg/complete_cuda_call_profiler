#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasLtMatmulDescGetAttribute)(cublasLtMatmulDesc_t, cublasLtMatmulDescAttributes_t, void *, size_t, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	cublasStatus_t cublasLtMatmulDescGetAttribute(cublasLtMatmulDesc_t matmulDesc, cublasLtMatmulDescAttributes_t attr, void *buf, size_t sizeInBytes, size_t *sizeWritten) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtMatmulDescGetAttribute)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtMatmulDescGetAttribute = (cublasStatus_t (*)(cublasLtMatmulDesc_t, cublasLtMatmulDescAttributes_t, void *, size_t, size_t *)) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtMatmulDescGetAttribute");
			fprintf(stderr, "wrapper_cublasLtMatmulDescGetAttribute:%p\n", wrapper_cublasLtMatmulDescGetAttribute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtMatmulDescGetAttribute():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasLtMatmulDescGetAttribute(matmulDesc, attr, buf, sizeInBytes, sizeWritten);
		return retval;
	}
}