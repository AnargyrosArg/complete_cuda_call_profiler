#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasZgemvStridedBatched)(cublasHandle_t, cublasOperation_t, int, int, const cuDoubleComplex *, const cuDoubleComplex *, int, long long int, const cuDoubleComplex *, int, long long int, const cuDoubleComplex *, cuDoubleComplex *, int, long long int, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasZgemvStridedBatched(cublasHandle_t handle, cublasOperation_t trans, int m, int n, const cuDoubleComplex *alpha, const cuDoubleComplex *A, int lda, long long int strideA, const cuDoubleComplex *x, int incx, long long int stridex, const cuDoubleComplex *beta, cuDoubleComplex *y, int incy, long long int stridey, int batchCount) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasZgemvStridedBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasZgemvStridedBatched = (cublasStatus_t (*)(cublasHandle_t, cublasOperation_t, int, int, const cuDoubleComplex *, const cuDoubleComplex *, int, long long int, const cuDoubleComplex *, int, long long int, const cuDoubleComplex *, cuDoubleComplex *, int, long long int, int)) dlsym(libwrapper_handle, "wrapper_cublasZgemvStridedBatched");
			fprintf(stderr, "wrapper_cublasZgemvStridedBatched:%p\n", wrapper_cublasZgemvStridedBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasZgemvStridedBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasZgemvStridedBatched(handle, trans, m, n, alpha, A, lda, strideA, x, incx, stridex, beta, y, incy, stridey, batchCount);
		return retval;
	}
}