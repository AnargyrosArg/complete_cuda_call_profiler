#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasDgetriBatched)(cublasHandle_t, int, const double * const*, int, const int *, double * const*, int, int *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasDgetriBatched(cublasHandle_t handle, int n, const double * const A[], int lda, const int *P, double * const C[], int ldc, int *info, int batchSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasDgetriBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasDgetriBatched = (cublasStatus_t (*)(cublasHandle_t, int, const double * const*, int, const int *, double * const*, int, int *, int)) dlsym(libwrapper_handle, "wrapper_cublasDgetriBatched");
			fprintf(stderr, "wrapper_cublasDgetriBatched:%p\n", wrapper_cublasDgetriBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasDgetriBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasDgetriBatched(handle, n, A, lda, P, C, ldc, info, batchSize);
		return retval;
	}
}