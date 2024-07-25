#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasZgeqrfBatched)(cublasHandle_t, int, int, cuDoubleComplex * const *, int, cuDoubleComplex * const *, int *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasZgeqrfBatched(cublasHandle_t handle, int m, int n, cuDoubleComplex * const Aarray[], int lda, cuDoubleComplex * const TauArray[], int *info, int batchSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasZgeqrfBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasZgeqrfBatched = (cublasStatus_t (*)(cublasHandle_t, int, int, cuDoubleComplex * const *, int, cuDoubleComplex * const *, int *, int)) dlsym(libwrapper_handle, "wrapper_cublasZgeqrfBatched");
			fprintf(stderr, "wrapper_cublasZgeqrfBatched:%p\n", wrapper_cublasZgeqrfBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasZgeqrfBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasZgeqrfBatched(handle, m, n, Aarray, lda, TauArray, info, batchSize);
		return retval;
	}
}