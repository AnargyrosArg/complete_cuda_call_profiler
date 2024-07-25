#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasCgetrfBatched)(cublasHandle_t, int, cuComplex * const*, int, int *, int *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasCgetrfBatched(cublasHandle_t handle, int n, cuComplex * const A[], int lda, int *P, int *info, int batchSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasCgetrfBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasCgetrfBatched = (cublasStatus_t (*)(cublasHandle_t, int, cuComplex * const*, int, int *, int *, int)) dlsym(libwrapper_handle, "wrapper_cublasCgetrfBatched");
			fprintf(stderr, "wrapper_cublasCgetrfBatched:%p\n", wrapper_cublasCgetrfBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasCgetrfBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasCgetrfBatched(handle, n, A, lda, P, info, batchSize);
		return retval;
	}
}