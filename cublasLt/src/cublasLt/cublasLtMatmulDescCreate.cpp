#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasLtMatmulDescCreate)(cublasLtMatmulDesc_t *, cublasComputeType_t, cudaDataType_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	cublasStatus_t cublasLtMatmulDescCreate(cublasLtMatmulDesc_t *matmulDesc, cublasComputeType_t computeType, cudaDataType_t scaleType) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtMatmulDescCreate)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtMatmulDescCreate = (cublasStatus_t (*)(cublasLtMatmulDesc_t *, cublasComputeType_t, cudaDataType_t)) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtMatmulDescCreate");
			fprintf(stderr, "wrapper_cublasLtMatmulDescCreate:%p\n", wrapper_cublasLtMatmulDescCreate);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtMatmulDescCreate():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasLtMatmulDescCreate(matmulDesc, computeType, scaleType);
		return retval;
	}
}