#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasZgetrsBatched)(cublasHandle_t, cublasOperation_t, int, int, const cuDoubleComplex * const*, int, const int *, cuDoubleComplex * const*, int, int *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasZgetrsBatched(cublasHandle_t handle, cublasOperation_t trans, int n, int nrhs, const cuDoubleComplex * const Aarray[], int lda, const int *devIpiv, cuDoubleComplex * const Barray[], int ldb, int *info, int batchSize) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasZgetrsBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasZgetrsBatched = (cublasStatus_t (*)(cublasHandle_t, cublasOperation_t, int, int, const cuDoubleComplex * const*, int, const int *, cuDoubleComplex * const*, int, int *, int)) dlsym(libwrapper_handle, "wrapper_cublasZgetrsBatched");
			fprintf(stderr, "wrapper_cublasZgetrsBatched:%p\n", wrapper_cublasZgetrsBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasZgetrsBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasZgetrsBatched(handle, trans, n, nrhs, Aarray, lda, devIpiv, Barray, ldb, info, batchSize);
		return retval;
	}
}