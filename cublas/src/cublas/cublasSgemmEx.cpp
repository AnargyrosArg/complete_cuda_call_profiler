#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasSgemmEx)(cublasHandle_t, cublasOperation_t, cublasOperation_t, int, int, int, const float *, const void *, cudaDataType, int, const void *, cudaDataType, int, const float *, void *, cudaDataType, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasSgemmEx(cublasHandle_t handle, cublasOperation_t transa, cublasOperation_t transb, int m, int n, int k, const float *alpha, const void *A, cudaDataType Atype, int lda, const void *B, cudaDataType Btype, int ldb, const float *beta, void *C, cudaDataType Ctype, int ldc) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasSgemmEx)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasSgemmEx = (cublasStatus_t (*)(cublasHandle_t, cublasOperation_t, cublasOperation_t, int, int, int, const float *, const void *, cudaDataType, int, const void *, cudaDataType, int, const float *, void *, cudaDataType, int)) dlsym(libwrapper_handle, "wrapper_cublasSgemmEx");
			fprintf(stderr, "wrapper_cublasSgemmEx:%p\n", wrapper_cublasSgemmEx);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasSgemmEx():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasSgemmEx(handle, transa, transb, m, n, k, alpha, A, Atype, lda, B, Btype, ldb, beta, C, Ctype, ldc);
		return retval;
	}
}