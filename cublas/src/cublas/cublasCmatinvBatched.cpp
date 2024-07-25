#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasCmatinvBatched)(cublasHandle_t, int, const cuComplex * const*, int, cuComplex * const*, int, int *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasCmatinvBatched(cublasHandle_t handle, int n, const cuComplex * const A[], int lda, cuComplex * const Ainv[], int lda_inv, int *info, int batchSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasCmatinvBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasCmatinvBatched = (cublasStatus_t (*)(cublasHandle_t, int, const cuComplex * const*, int, cuComplex * const*, int, int *, int)) dlsym(libwrapper_handle, "wrapper_cublasCmatinvBatched");
			fprintf(stderr, "wrapper_cublasCmatinvBatched:%p\n", wrapper_cublasCmatinvBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasCmatinvBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasCmatinvBatched(handle, n, A, lda, Ainv, lda_inv, info, batchSize);
		return retval;
	}
}