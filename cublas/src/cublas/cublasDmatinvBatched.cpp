#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasDmatinvBatched)(cublasHandle_t, int, const double * const *, int, double * const *, int, int *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasDmatinvBatched(cublasHandle_t handle, int n, const double * const A[], int lda, double * const Ainv[], int lda_inv, int *info, int batchSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasDmatinvBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasDmatinvBatched = (cublasStatus_t (*)(cublasHandle_t, int, const double * const *, int, double * const *, int, int *, int)) dlsym(libwrapper_handle, "wrapper_cublasDmatinvBatched");
			fprintf(stderr, "wrapper_cublasDmatinvBatched:%p\n", wrapper_cublasDmatinvBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasDmatinvBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasDmatinvBatched(handle, n, A, lda, Ainv, lda_inv, info, batchSize);
		return retval;
	}
}