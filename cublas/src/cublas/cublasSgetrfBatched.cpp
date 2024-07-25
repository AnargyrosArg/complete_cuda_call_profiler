#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasSgetrfBatched)(cublasHandle_t, int, float * const*, int, int *, int *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasSgetrfBatched(cublasHandle_t handle, int n, float * const A[], int lda, int *P, int *info, int batchSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasSgetrfBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasSgetrfBatched = (cublasStatus_t (*)(cublasHandle_t, int, float * const*, int, int *, int *, int)) dlsym(libwrapper_handle, "wrapper_cublasSgetrfBatched");
			fprintf(stderr, "wrapper_cublasSgetrfBatched:%p\n", wrapper_cublasSgetrfBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasSgetrfBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasSgetrfBatched(handle, n, A, lda, P, info, batchSize);
		return retval;
	}
}