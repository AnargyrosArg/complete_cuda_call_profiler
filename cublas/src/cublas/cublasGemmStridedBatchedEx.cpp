#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasGemmStridedBatchedEx)(cublasHandle_t, cublasOperation_t, cublasOperation_t, int, int, int, const void *, const void *, cudaDataType, int, long long int, const void *, cudaDataType, int, long long int, const void *, void *, cudaDataType, int, long long int, int, cublasComputeType_t, cublasGemmAlgo_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasGemmStridedBatchedEx(cublasHandle_t handle, cublasOperation_t transa, cublasOperation_t transb, int m, int n, int k, const void *alpha, const void *A, cudaDataType Atype, int lda, long long int strideA, const void *B, cudaDataType Btype, int ldb, long long int strideB, const void *beta, void *C, cudaDataType Ctype, int ldc, long long int strideC, int batchCount, cublasComputeType_t computeType, cublasGemmAlgo_t algo) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasGemmStridedBatchedEx)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasGemmStridedBatchedEx = (cublasStatus_t (*)(cublasHandle_t, cublasOperation_t, cublasOperation_t, int, int, int, const void *, const void *, cudaDataType, int, long long int, const void *, cudaDataType, int, long long int, const void *, void *, cudaDataType, int, long long int, int, cublasComputeType_t, cublasGemmAlgo_t)) dlsym(libwrapper_handle, "wrapper_cublasGemmStridedBatchedEx");
			fprintf(stderr, "wrapper_cublasGemmStridedBatchedEx:%p\n", wrapper_cublasGemmStridedBatchedEx);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasGemmStridedBatchedEx():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasGemmStridedBatchedEx(handle, transa, transb, m, n, k, alpha, A, Atype, lda, strideA, B, Btype, ldb, strideB, beta, C, Ctype, ldc, strideC, batchCount, computeType, algo);
		return retval;
	}
}