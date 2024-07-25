#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasCgetriBatched)(cublasHandle_t, int, const cuComplex * const*, int, const int *, cuComplex * const*, int, int *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasCgetriBatched(cublasHandle_t handle, int n, const cuComplex * const A[], int lda, const int *P, cuComplex * const C[], int ldc, int *info, int batchSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasCgetriBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasCgetriBatched = (cublasStatus_t (*)(cublasHandle_t, int, const cuComplex * const*, int, const int *, cuComplex * const*, int, int *, int)) dlsym(libwrapper_handle, "wrapper_cublasCgetriBatched");
			fprintf(stderr, "wrapper_cublasCgetriBatched:%p\n", wrapper_cublasCgetriBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasCgetriBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasCgetriBatched(handle, n, A, lda, P, C, ldc, info, batchSize);
		return retval;
	}
}