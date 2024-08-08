#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasDgemvBatched)(cublasHandle_t, cublasOperation_t, int, int, const double *, const double * const *, int, const double * const *, int, const double *, double * const *, int, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasDgemvBatched(cublasHandle_t handle, cublasOperation_t trans, int m, int n, const double *alpha, const double * const Aarray[], int lda, const double * const xarray[], int incx, const double *beta, double * const yarray[], int incy, int batchCount) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasDgemvBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasDgemvBatched = (cublasStatus_t (*)(cublasHandle_t, cublasOperation_t, int, int, const double *, const double * const *, int, const double * const *, int, const double *, double * const *, int, int)) dlsym(libwrapper_handle, "wrapper_cublasDgemvBatched");
			fprintf(stderr, "wrapper_cublasDgemvBatched:%p\n", wrapper_cublasDgemvBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasDgemvBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasDgemvBatched(handle, trans, m, n, alpha, Aarray, lda, xarray, incx, beta, yarray, incy, batchCount);
		return retval;
	}
}