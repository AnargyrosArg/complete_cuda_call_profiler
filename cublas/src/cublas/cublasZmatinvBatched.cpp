#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasZmatinvBatched)(cublasHandle_t, int, const cuDoubleComplex * const*, int, cuDoubleComplex * const*, int, int *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasZmatinvBatched(cublasHandle_t handle, int n, const cuDoubleComplex * const A[], int lda, cuDoubleComplex * const Ainv[], int lda_inv, int *info, int batchSize) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasZmatinvBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasZmatinvBatched = (cublasStatus_t (*)(cublasHandle_t, int, const cuDoubleComplex * const*, int, cuDoubleComplex * const*, int, int *, int)) dlsym(libwrapper_handle, "wrapper_cublasZmatinvBatched");
			fprintf(stderr, "wrapper_cublasZmatinvBatched:%p\n", wrapper_cublasZmatinvBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasZmatinvBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasZmatinvBatched(handle, n, A, lda, Ainv, lda_inv, info, batchSize);
		return retval;
	}
}