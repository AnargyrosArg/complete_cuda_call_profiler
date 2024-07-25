#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasSgemmBatched)(cublasHandle_t, cublasOperation_t, cublasOperation_t, int, int, int, const float *, const float * const *, int, const float * const *, int, const float *, float * const *, int, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasSgemmBatched(cublasHandle_t handle, cublasOperation_t transa, cublasOperation_t transb, int m, int n, int k, const float *alpha, const float * const Aarray[], int lda, const float * const Barray[], int ldb, const float *beta, float * const Carray[], int ldc, int batchCount) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasSgemmBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasSgemmBatched = (cublasStatus_t (*)(cublasHandle_t, cublasOperation_t, cublasOperation_t, int, int, int, const float *, const float * const *, int, const float * const *, int, const float *, float * const *, int, int)) dlsym(libwrapper_handle, "wrapper_cublasSgemmBatched");
			fprintf(stderr, "wrapper_cublasSgemmBatched:%p\n", wrapper_cublasSgemmBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasSgemmBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasSgemmBatched(handle, transa, transb, m, n, k, alpha, Aarray, lda, Barray, ldb, beta, Carray, ldc, batchCount);
		return retval;
	}
}