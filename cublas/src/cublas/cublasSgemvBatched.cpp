#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasSgemvBatched)(cublasHandle_t, cublasOperation_t, int, int, const float *, const float * const*, int, const float * const*, int, const float *, float * const*, int, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasSgemvBatched(cublasHandle_t handle, cublasOperation_t trans, int m, int n, const float *alpha, const float * const Aarray[], int lda, const float * const xarray[], int incx, const float *beta, float * const yarray[], int incy, int batchCount) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasSgemvBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasSgemvBatched = (cublasStatus_t (*)(cublasHandle_t, cublasOperation_t, int, int, const float *, const float * const*, int, const float * const*, int, const float *, float * const*, int, int)) dlsym(libwrapper_handle, "wrapper_cublasSgemvBatched");
			fprintf(stderr, "wrapper_cublasSgemvBatched:%p\n", wrapper_cublasSgemvBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasSgemvBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasSgemvBatched(handle, trans, m, n, alpha, Aarray, lda, xarray, incx, beta, yarray, incy, batchCount);
		return retval;
	}
}