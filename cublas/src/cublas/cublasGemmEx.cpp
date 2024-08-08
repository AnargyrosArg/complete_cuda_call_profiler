#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasGemmEx)(cublasHandle_t, cublasOperation_t, cublasOperation_t, int, int, int, const void *, const void *, cudaDataType, int, const void *, cudaDataType, int, const void *, void *, cudaDataType, int, cublasComputeType_t, cublasGemmAlgo_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasGemmEx(cublasHandle_t handle, cublasOperation_t transa, cublasOperation_t transb, int m, int n, int k, const void *alpha, const void *A, cudaDataType Atype, int lda, const void *B, cudaDataType Btype, int ldb, const void *beta, void *C, cudaDataType Ctype, int ldc, cublasComputeType_t computeType, cublasGemmAlgo_t algo) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasGemmEx)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasGemmEx = (cublasStatus_t (*)(cublasHandle_t, cublasOperation_t, cublasOperation_t, int, int, int, const void *, const void *, cudaDataType, int, const void *, cudaDataType, int, const void *, void *, cudaDataType, int, cublasComputeType_t, cublasGemmAlgo_t)) dlsym(libwrapper_handle, "wrapper_cublasGemmEx");
			fprintf(stderr, "wrapper_cublasGemmEx:%p\n", wrapper_cublasGemmEx);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasGemmEx():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasGemmEx(handle, transa, transb, m, n, k, alpha, A, Atype, lda, B, Btype, ldb, beta, C, Ctype, ldc, computeType, algo);
		return retval;
	}
}