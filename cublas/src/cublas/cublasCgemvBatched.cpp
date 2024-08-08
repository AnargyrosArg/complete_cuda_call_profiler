#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasCgemvBatched)(cublasHandle_t, cublasOperation_t, int, int, const cuComplex *, const cuComplex * const *, int, const cuComplex * const *, int, const cuComplex *, cuComplex * const *, int, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasCgemvBatched(cublasHandle_t handle, cublasOperation_t trans, int m, int n, const cuComplex *alpha, const cuComplex * const Aarray[], int lda, const cuComplex * const xarray[], int incx, const cuComplex *beta, cuComplex * const yarray[], int incy, int batchCount) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasCgemvBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasCgemvBatched = (cublasStatus_t (*)(cublasHandle_t, cublasOperation_t, int, int, const cuComplex *, const cuComplex * const *, int, const cuComplex * const *, int, const cuComplex *, cuComplex * const *, int, int)) dlsym(libwrapper_handle, "wrapper_cublasCgemvBatched");
			fprintf(stderr, "wrapper_cublasCgemvBatched:%p\n", wrapper_cublasCgemvBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasCgemvBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasCgemvBatched(handle, trans, m, n, alpha, Aarray, lda, xarray, incx, beta, yarray, incy, batchCount);
		return retval;
	}
}