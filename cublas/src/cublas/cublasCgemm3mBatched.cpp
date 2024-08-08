#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasCgemm3mBatched)(cublasHandle_t, cublasOperation_t, cublasOperation_t, int, int, int, const cuComplex *, const cuComplex * const*, int, const cuComplex * const*, int, const cuComplex *, cuComplex * const*, int, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasCgemm3mBatched(cublasHandle_t handle, cublasOperation_t transa, cublasOperation_t transb, int m, int n, int k, const cuComplex *alpha, const cuComplex * const Aarray[], int lda, const cuComplex * const Barray[], int ldb, const cuComplex *beta, cuComplex * const Carray[], int ldc, int batchCount) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasCgemm3mBatched)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasCgemm3mBatched = (cublasStatus_t (*)(cublasHandle_t, cublasOperation_t, cublasOperation_t, int, int, int, const cuComplex *, const cuComplex * const*, int, const cuComplex * const*, int, const cuComplex *, cuComplex * const*, int, int)) dlsym(libwrapper_handle, "wrapper_cublasCgemm3mBatched");
			fprintf(stderr, "wrapper_cublasCgemm3mBatched:%p\n", wrapper_cublasCgemm3mBatched);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasCgemm3mBatched():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasCgemm3mBatched(handle, transa, transb, m, n, k, alpha, Aarray, lda, Barray, ldb, beta, Carray, ldc, batchCount);
		return retval;
	}
}