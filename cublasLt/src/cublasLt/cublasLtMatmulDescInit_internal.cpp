#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasLtMatmulDescInit_internal)(cublasLtMatmulDesc_t, size_t, cublasComputeType_t, cudaDataType_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	cublasStatus_t cublasLtMatmulDescInit_internal(cublasLtMatmulDesc_t matmulDesc, size_t size, cublasComputeType_t computeType, cudaDataType_t scaleType) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtMatmulDescInit_internal)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtMatmulDescInit_internal = (cublasStatus_t (*)(cublasLtMatmulDesc_t, size_t, cublasComputeType_t, cudaDataType_t)) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtMatmulDescInit_internal");
			fprintf(stderr, "wrapper_cublasLtMatmulDescInit_internal:%p\n", wrapper_cublasLtMatmulDescInit_internal);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtMatmulDescInit_internal():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasLtMatmulDescInit_internal(matmulDesc, size, computeType, scaleType);
		return retval;
	}
}