#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasZgetriBatched)(cublasHandle_t, int, const cuDoubleComplex * const*, int, const int *, cuDoubleComplex * const*, int, int *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasZgetriBatched(cublasHandle_t handle, int n, const cuDoubleComplex * const A[], int lda, const int *P, cuDoubleComplex * const C[], int ldc, int *info, int batchSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasZgetriBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasZgetriBatched = (cublasStatus_t (*)(cublasHandle_t, int, const cuDoubleComplex * const*, int, const int *, cuDoubleComplex * const*, int, int *, int)) dlsym(libwrapper_handle, "wrapper_cublasZgetriBatched");
			fprintf(stderr, "wrapper_cublasZgetriBatched:%p\n", wrapper_cublasZgetriBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasZgetriBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasZgetriBatched(handle, n, A, lda, P, C, ldc, info, batchSize);
		return retval;
	}
}