#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasDgelsBatched)(cublasHandle_t, cublasOperation_t, int, int, int, double * const*, int, double * const*, int, int *, int *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasDgelsBatched(cublasHandle_t handle, cublasOperation_t trans, int m, int n, int nrhs, double * const Aarray[], int lda, double * const Carray[], int ldc, int *info, int *devInfoArray, int batchSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasDgelsBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasDgelsBatched = (cublasStatus_t (*)(cublasHandle_t, cublasOperation_t, int, int, int, double * const*, int, double * const*, int, int *, int *, int)) dlsym(libwrapper_handle, "wrapper_cublasDgelsBatched");
			fprintf(stderr, "wrapper_cublasDgelsBatched:%p\n", wrapper_cublasDgelsBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasDgelsBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasDgelsBatched(handle, trans, m, n, nrhs, Aarray, lda, Carray, ldc, info, devInfoArray, batchSize);
		return retval;
	}
}