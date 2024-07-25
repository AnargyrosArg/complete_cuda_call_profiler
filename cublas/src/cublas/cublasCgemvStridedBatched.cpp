#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasCgemvStridedBatched)(cublasHandle_t, cublasOperation_t, int, int, const cuComplex *, const cuComplex *, int, long long int, const cuComplex *, int, long long int, const cuComplex *, cuComplex *, int, long long int, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasCgemvStridedBatched(cublasHandle_t handle, cublasOperation_t trans, int m, int n, const cuComplex *alpha, const cuComplex *A, int lda, long long int strideA, const cuComplex *x, int incx, long long int stridex, const cuComplex *beta, cuComplex *y, int incy, long long int stridey, int batchCount) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasCgemvStridedBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasCgemvStridedBatched = (cublasStatus_t (*)(cublasHandle_t, cublasOperation_t, int, int, const cuComplex *, const cuComplex *, int, long long int, const cuComplex *, int, long long int, const cuComplex *, cuComplex *, int, long long int, int)) dlsym(libwrapper_handle, "wrapper_cublasCgemvStridedBatched");
			fprintf(stderr, "wrapper_cublasCgemvStridedBatched:%p\n", wrapper_cublasCgemvStridedBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasCgemvStridedBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasCgemvStridedBatched(handle, trans, m, n, alpha, A, lda, strideA, x, incx, stridex, beta, y, incy, stridey, batchCount);
		return retval;
	}
}