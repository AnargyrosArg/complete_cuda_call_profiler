#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasSsyr2k_v2)(cublasHandle_t, cublasFillMode_t, cublasOperation_t, int, int, const float *, const float *, int, const float *, int, const float *, float *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasSsyr2k_v2(cublasHandle_t handle, cublasFillMode_t uplo, cublasOperation_t trans, int n, int k, const float *alpha, const float *A, int lda, const float *B, int ldb, const float *beta, float *C, int ldc) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasSsyr2k_v2)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasSsyr2k_v2 = (cublasStatus_t (*)(cublasHandle_t, cublasFillMode_t, cublasOperation_t, int, int, const float *, const float *, int, const float *, int, const float *, float *, int)) dlsym(libwrapper_handle, "wrapper_cublasSsyr2k_v2");
			fprintf(stderr, "wrapper_cublasSsyr2k_v2:%p\n", wrapper_cublasSsyr2k_v2);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasSsyr2k_v2():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasSsyr2k_v2(handle, uplo, trans, n, k, alpha, A, lda, B, ldb, beta, C, ldc);
		return retval;
	}
}