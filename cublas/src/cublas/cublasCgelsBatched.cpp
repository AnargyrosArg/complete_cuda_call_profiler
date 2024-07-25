#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasCgelsBatched)(cublasHandle_t, cublasOperation_t, int, int, int, cuComplex * const*, int, cuComplex * const*, int, int *, int *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasCgelsBatched(cublasHandle_t handle, cublasOperation_t trans, int m, int n, int nrhs, cuComplex * const Aarray[], int lda, cuComplex * const Carray[], int ldc, int *info, int *devInfoArray, int batchSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasCgelsBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasCgelsBatched = (cublasStatus_t (*)(cublasHandle_t, cublasOperation_t, int, int, int, cuComplex * const*, int, cuComplex * const*, int, int *, int *, int)) dlsym(libwrapper_handle, "wrapper_cublasCgelsBatched");
			fprintf(stderr, "wrapper_cublasCgelsBatched:%p\n", wrapper_cublasCgelsBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasCgelsBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasCgelsBatched(handle, trans, m, n, nrhs, Aarray, lda, Carray, ldc, info, devInfoArray, batchSize);
		return retval;
	}
}