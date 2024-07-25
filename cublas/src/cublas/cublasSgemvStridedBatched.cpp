#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasSgemvStridedBatched)(cublasHandle_t, cublasOperation_t, int, int, const float *, const float *, int, long long int, const float *, int, long long int, const float *, float *, int, long long int, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasSgemvStridedBatched(cublasHandle_t handle, cublasOperation_t trans, int m, int n, const float *alpha, const float *A, int lda, long long int strideA, const float *x, int incx, long long int stridex, const float *beta, float *y, int incy, long long int stridey, int batchCount) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasSgemvStridedBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasSgemvStridedBatched = (cublasStatus_t (*)(cublasHandle_t, cublasOperation_t, int, int, const float *, const float *, int, long long int, const float *, int, long long int, const float *, float *, int, long long int, int)) dlsym(libwrapper_handle, "wrapper_cublasSgemvStridedBatched");
			fprintf(stderr, "wrapper_cublasSgemvStridedBatched:%p\n", wrapper_cublasSgemvStridedBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasSgemvStridedBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasSgemvStridedBatched(handle, trans, m, n, alpha, A, lda, strideA, x, incx, stridex, beta, y, incy, stridey, batchCount);
		return retval;
	}
}