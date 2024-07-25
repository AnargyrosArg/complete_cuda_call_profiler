#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasLtMatmulAlgoInit)(cublasLtHandle_t, cublasComputeType_t, cudaDataType_t, cudaDataType_t, cudaDataType_t, cudaDataType_t, cudaDataType_t, int, cublasLtMatmulAlgo_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	cublasStatus_t cublasLtMatmulAlgoInit(cublasLtHandle_t lightHandle, cublasComputeType_t computeType, cudaDataType_t scaleType, cudaDataType_t Atype, cudaDataType_t Btype, cudaDataType_t Ctype, cudaDataType_t Dtype, int algoId, cublasLtMatmulAlgo_t *algo) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtMatmulAlgoInit)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtMatmulAlgoInit = (cublasStatus_t (*)(cublasLtHandle_t, cublasComputeType_t, cudaDataType_t, cudaDataType_t, cudaDataType_t, cudaDataType_t, cudaDataType_t, int, cublasLtMatmulAlgo_t *)) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtMatmulAlgoInit");
			fprintf(stderr, "wrapper_cublasLtMatmulAlgoInit:%p\n", wrapper_cublasLtMatmulAlgoInit);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtMatmulAlgoInit():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasLtMatmulAlgoInit(lightHandle, computeType, scaleType, Atype, Btype, Ctype, Dtype, algoId, algo);
		return retval;
	}
}