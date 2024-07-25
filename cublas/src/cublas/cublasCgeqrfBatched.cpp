#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasCgeqrfBatched)(cublasHandle_t, int, int, cuComplex * const *, int, cuComplex * const *, int *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasCgeqrfBatched(cublasHandle_t handle, int m, int n, cuComplex * const Aarray[], int lda, cuComplex * const TauArray[], int *info, int batchSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasCgeqrfBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasCgeqrfBatched = (cublasStatus_t (*)(cublasHandle_t, int, int, cuComplex * const *, int, cuComplex * const *, int *, int)) dlsym(libwrapper_handle, "wrapper_cublasCgeqrfBatched");
			fprintf(stderr, "wrapper_cublasCgeqrfBatched:%p\n", wrapper_cublasCgeqrfBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasCgeqrfBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasCgeqrfBatched(handle, m, n, Aarray, lda, TauArray, info, batchSize);
		return retval;
	}
}