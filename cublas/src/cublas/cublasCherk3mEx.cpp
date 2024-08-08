#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasCherk3mEx)(cublasHandle_t, cublasFillMode_t, cublasOperation_t, int, int, const float *, const void *, cudaDataType, int, const float *, void *, cudaDataType, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasCherk3mEx(cublasHandle_t handle, cublasFillMode_t uplo, cublasOperation_t trans, int n, int k, const float *alpha, const void *A, cudaDataType Atype, int lda, const float *beta, void *C, cudaDataType Ctype, int ldc) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasCherk3mEx)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasCherk3mEx = (cublasStatus_t (*)(cublasHandle_t, cublasFillMode_t, cublasOperation_t, int, int, const float *, const void *, cudaDataType, int, const float *, void *, cudaDataType, int)) dlsym(libwrapper_handle, "wrapper_cublasCherk3mEx");
			fprintf(stderr, "wrapper_cublasCherk3mEx:%p\n", wrapper_cublasCherk3mEx);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasCherk3mEx():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasCherk3mEx(handle, uplo, trans, n, k, alpha, A, Atype, lda, beta, C, Ctype, ldc);
		return retval;
	}
}