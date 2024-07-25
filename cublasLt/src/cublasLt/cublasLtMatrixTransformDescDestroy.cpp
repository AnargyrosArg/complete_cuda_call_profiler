#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasLtMatrixTransformDescDestroy)(cublasLtMatrixTransformDesc_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	cublasStatus_t cublasLtMatrixTransformDescDestroy(cublasLtMatrixTransformDesc_t transformDesc) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtMatrixTransformDescDestroy)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtMatrixTransformDescDestroy = (cublasStatus_t (*)(cublasLtMatrixTransformDesc_t)) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtMatrixTransformDescDestroy");
			fprintf(stderr, "wrapper_cublasLtMatrixTransformDescDestroy:%p\n", wrapper_cublasLtMatrixTransformDescDestroy);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtMatrixTransformDescDestroy():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasLtMatrixTransformDescDestroy(transformDesc);
		return retval;
	}
}