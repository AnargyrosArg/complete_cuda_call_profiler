#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasZgemmBatched)(cublasHandle_t, cublasOperation_t, cublasOperation_t, int, int, int, const cuDoubleComplex *, const cuDoubleComplex * const*, int, const cuDoubleComplex * const*, int, const cuDoubleComplex *, cuDoubleComplex * const*, int, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasZgemmBatched(cublasHandle_t handle, cublasOperation_t transa, cublasOperation_t transb, int m, int n, int k, const cuDoubleComplex *alpha, const cuDoubleComplex * const Aarray[], int lda, const cuDoubleComplex * const Barray[], int ldb, const cuDoubleComplex *beta, cuDoubleComplex * const Carray[], int ldc, int batchCount) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasZgemmBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasZgemmBatched = (cublasStatus_t (*)(cublasHandle_t, cublasOperation_t, cublasOperation_t, int, int, int, const cuDoubleComplex *, const cuDoubleComplex * const*, int, const cuDoubleComplex * const*, int, const cuDoubleComplex *, cuDoubleComplex * const*, int, int)) dlsym(libwrapper_handle, "wrapper_cublasZgemmBatched");
			fprintf(stderr, "wrapper_cublasZgemmBatched:%p\n", wrapper_cublasZgemmBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasZgemmBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasZgemmBatched(handle, transa, transb, m, n, k, alpha, Aarray, lda, Barray, ldb, beta, Carray, ldc, batchCount);
		return retval;
	}
}