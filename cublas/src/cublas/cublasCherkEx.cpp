#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasCherkEx)(cublasHandle_t, cublasFillMode_t, cublasOperation_t, int, int, const float *, const void *, cudaDataType, int, const float *, void *, cudaDataType, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasCherkEx(cublasHandle_t handle, cublasFillMode_t uplo, cublasOperation_t trans, int n, int k, const float *alpha, const void *A, cudaDataType Atype, int lda, const float *beta, void *C, cudaDataType Ctype, int ldc) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasCherkEx)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasCherkEx = (cublasStatus_t (*)(cublasHandle_t, cublasFillMode_t, cublasOperation_t, int, int, const float *, const void *, cudaDataType, int, const float *, void *, cudaDataType, int)) dlsym(libwrapper_handle, "wrapper_cublasCherkEx");
			fprintf(stderr, "wrapper_cublasCherkEx:%p\n", wrapper_cublasCherkEx);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasCherkEx():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasCherkEx(handle, uplo, trans, n, k, alpha, A, Atype, lda, beta, C, Ctype, ldc);
		return retval;
	}
}