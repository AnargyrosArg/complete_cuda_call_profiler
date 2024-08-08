#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasDgemvStridedBatched)(cublasHandle_t, cublasOperation_t, int, int, const double *, const double *, int, long long int, const double *, int, long long int, const double *, double *, int, long long int, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasDgemvStridedBatched(cublasHandle_t handle, cublasOperation_t trans, int m, int n, const double *alpha, const double *A, int lda, long long int strideA, const double *x, int incx, long long int stridex, const double *beta, double *y, int incy, long long int stridey, int batchCount) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasDgemvStridedBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasDgemvStridedBatched = (cublasStatus_t (*)(cublasHandle_t, cublasOperation_t, int, int, const double *, const double *, int, long long int, const double *, int, long long int, const double *, double *, int, long long int, int)) dlsym(libwrapper_handle, "wrapper_cublasDgemvStridedBatched");
			fprintf(stderr, "wrapper_cublasDgemvStridedBatched:%p\n", wrapper_cublasDgemvStridedBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasDgemvStridedBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasDgemvStridedBatched(handle, trans, m, n, alpha, A, lda, strideA, x, incx, stridex, beta, y, incy, stridey, batchCount);
		return retval;
	}
}