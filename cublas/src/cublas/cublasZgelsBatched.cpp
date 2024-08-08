#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasZgelsBatched)(cublasHandle_t, cublasOperation_t, int, int, int, cuDoubleComplex * const *, int, cuDoubleComplex * const *, int, int *, int *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasZgelsBatched(cublasHandle_t handle, cublasOperation_t trans, int m, int n, int nrhs, cuDoubleComplex * const Aarray[], int lda, cuDoubleComplex * const Carray[], int ldc, int *info, int *devInfoArray, int batchSize) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasZgelsBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasZgelsBatched = (cublasStatus_t (*)(cublasHandle_t, cublasOperation_t, int, int, int, cuDoubleComplex * const *, int, cuDoubleComplex * const *, int, int *, int *, int)) dlsym(libwrapper_handle, "wrapper_cublasZgelsBatched");
			fprintf(stderr, "wrapper_cublasZgelsBatched:%p\n", wrapper_cublasZgelsBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasZgelsBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasZgelsBatched(handle, trans, m, n, nrhs, Aarray, lda, Carray, ldc, info, devInfoArray, batchSize);
		return retval;
	}
}