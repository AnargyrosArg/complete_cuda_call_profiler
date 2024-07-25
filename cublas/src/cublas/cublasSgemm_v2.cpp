#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasSgemm_v2)(cublasHandle_t, cublasOperation_t, cublasOperation_t, int, int, int, const float *, const float *, int, const float *, int, const float *, float *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasSgemm_v2(cublasHandle_t handle, cublasOperation_t transa, cublasOperation_t transb, int m, int n, int k, const float *alpha, const float *A, int lda, const float *B, int ldb, const float *beta, float *C, int ldc) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasSgemm_v2)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasSgemm_v2 = (cublasStatus_t (*)(cublasHandle_t, cublasOperation_t, cublasOperation_t, int, int, int, const float *, const float *, int, const float *, int, const float *, float *, int)) dlsym(libwrapper_handle, "wrapper_cublasSgemm_v2");
			fprintf(stderr, "wrapper_cublasSgemm_v2:%p\n", wrapper_cublasSgemm_v2);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasSgemm_v2():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasSgemm_v2(handle, transa, transb, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc);
		return retval;
	}
}