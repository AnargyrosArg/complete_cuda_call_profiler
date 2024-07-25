#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasLtMatrixTransformDescSetAttribute)(cublasLtMatrixTransformDesc_t, cublasLtMatrixTransformDescAttributes_t, const void *, size_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	cublasStatus_t cublasLtMatrixTransformDescSetAttribute(cublasLtMatrixTransformDesc_t transformDesc, cublasLtMatrixTransformDescAttributes_t attr, const void *buf, size_t sizeInBytes) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtMatrixTransformDescSetAttribute)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtMatrixTransformDescSetAttribute = (cublasStatus_t (*)(cublasLtMatrixTransformDesc_t, cublasLtMatrixTransformDescAttributes_t, const void *, size_t)) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtMatrixTransformDescSetAttribute");
			fprintf(stderr, "wrapper_cublasLtMatrixTransformDescSetAttribute:%p\n", wrapper_cublasLtMatrixTransformDescSetAttribute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtMatrixTransformDescSetAttribute():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasLtMatrixTransformDescSetAttribute(transformDesc, attr, buf, sizeInBytes);
		return retval;
	}
}