#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasUint8gemmBias)(cublasHandle_t, cublasOperation_t, cublasOperation_t, cublasOperation_t, int, int, int, const unsigned char *, int, int, const unsigned char *, int, int, unsigned char *, int, int, int, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasUint8gemmBias(cublasHandle_t handle, cublasOperation_t transa, cublasOperation_t transb, cublasOperation_t transc, int m, int n, int k, const unsigned char *A, int A_bias, int lda, const unsigned char *B, int B_bias, int ldb, unsigned char *C, int C_bias, int ldc, int C_mult, int C_shift) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasUint8gemmBias)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasUint8gemmBias = (cublasStatus_t (*)(cublasHandle_t, cublasOperation_t, cublasOperation_t, cublasOperation_t, int, int, int, const unsigned char *, int, int, const unsigned char *, int, int, unsigned char *, int, int, int, int)) dlsym(libwrapper_handle, "wrapper_cublasUint8gemmBias");
			fprintf(stderr, "wrapper_cublasUint8gemmBias:%p\n", wrapper_cublasUint8gemmBias);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasUint8gemmBias():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasUint8gemmBias(handle, transa, transb, transc, m, n, k, A, A_bias, lda, B, B_bias, ldb, C, C_bias, ldc, C_mult, C_shift);
		return retval;
	}
}