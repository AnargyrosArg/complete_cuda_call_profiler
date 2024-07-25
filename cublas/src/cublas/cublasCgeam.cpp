#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasCgeam)(cublasHandle_t, cublasOperation_t, cublasOperation_t, int, int, const cuComplex *, const cuComplex *, int, const cuComplex *, const cuComplex *, int, cuComplex *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasCgeam(cublasHandle_t handle, cublasOperation_t transa, cublasOperation_t transb, int m, int n, const cuComplex *alpha, const cuComplex *A, int lda, const cuComplex *beta, const cuComplex *B, int ldb, cuComplex *C, int ldc) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasCgeam)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasCgeam = (cublasStatus_t (*)(cublasHandle_t, cublasOperation_t, cublasOperation_t, int, int, const cuComplex *, const cuComplex *, int, const cuComplex *, const cuComplex *, int, cuComplex *, int)) dlsym(libwrapper_handle, "wrapper_cublasCgeam");
			fprintf(stderr, "wrapper_cublasCgeam:%p\n", wrapper_cublasCgeam);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasCgeam():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasCgeam(handle, transa, transb, m, n, alpha, A, lda, beta, B, ldb, C, ldc);
		return retval;
	}
}