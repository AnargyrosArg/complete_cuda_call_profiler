#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasZgetrfBatched)(cublasHandle_t, int, cuDoubleComplex * const*, int, int *, int *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasZgetrfBatched(cublasHandle_t handle, int n, cuDoubleComplex * const A[], int lda, int *P, int *info, int batchSize) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasZgetrfBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasZgetrfBatched = (cublasStatus_t (*)(cublasHandle_t, int, cuDoubleComplex * const*, int, int *, int *, int)) dlsym(libwrapper_handle, "wrapper_cublasZgetrfBatched");
			fprintf(stderr, "wrapper_cublasZgetrfBatched:%p\n", wrapper_cublasZgetrfBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasZgetrfBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasZgetrfBatched(handle, n, A, lda, P, info, batchSize);
		return retval;
	}
}