#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasGemmBatchedEx)(cublasHandle_t, cublasOperation_t, cublasOperation_t, int, int, int, const void *, const void * const*, cudaDataType, int, const void * const*, cudaDataType, int, const void *, void * const*, cudaDataType, int, int, cublasComputeType_t, cublasGemmAlgo_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasGemmBatchedEx(cublasHandle_t handle, cublasOperation_t transa, cublasOperation_t transb, int m, int n, int k, const void *alpha, const void * const Aarray[], cudaDataType Atype, int lda, const void * const Barray[], cudaDataType Btype, int ldb, const void *beta, void * const Carray[], cudaDataType Ctype, int ldc, int batchCount, cublasComputeType_t computeType, cublasGemmAlgo_t algo) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasGemmBatchedEx)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasGemmBatchedEx = (cublasStatus_t (*)(cublasHandle_t, cublasOperation_t, cublasOperation_t, int, int, int, const void *, const void * const*, cudaDataType, int, const void * const*, cudaDataType, int, const void *, void * const*, cudaDataType, int, int, cublasComputeType_t, cublasGemmAlgo_t)) dlsym(libwrapper_handle, "wrapper_cublasGemmBatchedEx");
			fprintf(stderr, "wrapper_cublasGemmBatchedEx:%p\n", wrapper_cublasGemmBatchedEx);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasGemmBatchedEx():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasGemmBatchedEx(handle, transa, transb, m, n, k, alpha, Aarray, Atype, lda, Barray, Btype, ldb, beta, Carray, Ctype, ldc, batchCount, computeType, algo);
		return retval;
	}
}