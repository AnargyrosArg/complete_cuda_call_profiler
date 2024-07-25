#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasLtMatrixTransformDescInit_internal)(cublasLtMatrixTransformDesc_t, size_t, cudaDataType);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	cublasStatus_t cublasLtMatrixTransformDescInit_internal(cublasLtMatrixTransformDesc_t transformDesc, size_t size, cudaDataType scaleType) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtMatrixTransformDescInit_internal)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtMatrixTransformDescInit_internal = (cublasStatus_t (*)(cublasLtMatrixTransformDesc_t, size_t, cudaDataType)) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtMatrixTransformDescInit_internal");
			fprintf(stderr, "wrapper_cublasLtMatrixTransformDescInit_internal:%p\n", wrapper_cublasLtMatrixTransformDescInit_internal);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtMatrixTransformDescInit_internal():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasLtMatrixTransformDescInit_internal(transformDesc, size, scaleType);
		return retval;
	}
}