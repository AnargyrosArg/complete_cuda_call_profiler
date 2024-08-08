#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasZgemvBatched)(cublasHandle_t, cublasOperation_t, int, int, const cuDoubleComplex *, const cuDoubleComplex * const *, int, const cuDoubleComplex * const *, int, const cuDoubleComplex *, cuDoubleComplex * const *, int, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasZgemvBatched(cublasHandle_t handle, cublasOperation_t trans, int m, int n, const cuDoubleComplex *alpha, const cuDoubleComplex * const Aarray[], int lda, const cuDoubleComplex * const xarray[], int incx, const cuDoubleComplex *beta, cuDoubleComplex * const yarray[], int incy, int batchCount) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasZgemvBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasZgemvBatched = (cublasStatus_t (*)(cublasHandle_t, cublasOperation_t, int, int, const cuDoubleComplex *, const cuDoubleComplex * const *, int, const cuDoubleComplex * const *, int, const cuDoubleComplex *, cuDoubleComplex * const *, int, int)) dlsym(libwrapper_handle, "wrapper_cublasZgemvBatched");
			fprintf(stderr, "wrapper_cublasZgemvBatched:%p\n", wrapper_cublasZgemvBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasZgemvBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasZgemvBatched(handle, trans, m, n, alpha, Aarray, lda, xarray, incx, beta, yarray, incy, batchCount);
		return retval;
	}
}