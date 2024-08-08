#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasLtMatmulAlgoGetIds)(cublasLtHandle_t, cublasComputeType_t, cudaDataType_t, cudaDataType_t, cudaDataType_t, cudaDataType_t, cudaDataType_t, int, int *, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	cublasStatus_t cublasLtMatmulAlgoGetIds(cublasLtHandle_t lightHandle, cublasComputeType_t computeType, cudaDataType_t scaleType, cudaDataType_t Atype, cudaDataType_t Btype, cudaDataType_t Ctype, cudaDataType_t Dtype, int requestedAlgoCount, int algoIdsArray[], int *returnAlgoCount){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtMatmulAlgoGetIds)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtMatmulAlgoGetIds = (cublasStatus_t (*)(cublasLtHandle_t, cublasComputeType_t, cudaDataType_t, cudaDataType_t, cudaDataType_t, cudaDataType_t, cudaDataType_t, int, int *, int *)) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtMatmulAlgoGetIds");
			fprintf(stderr, "wrapper_cublasLtMatmulAlgoGetIds:%p\n", wrapper_cublasLtMatmulAlgoGetIds);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtMatmulAlgoGetIds():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasLtMatmulAlgoGetIds(lightHandle, computeType, scaleType, Atype, Btype, Ctype, Dtype, requestedAlgoCount, algoIdsArray, returnAlgoCount);
		return retval;
	}
}