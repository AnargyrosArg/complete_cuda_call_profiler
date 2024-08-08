#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasCgemm3mEx)(cublasHandle_t, cublasOperation_t, cublasOperation_t, int, int, int, const cuComplex *, const void *, cudaDataType, int, const void *, cudaDataType, int, const cuComplex *, void *, cudaDataType, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasCgemm3mEx(cublasHandle_t handle, cublasOperation_t transa, cublasOperation_t transb, int m, int n, int k, const cuComplex *alpha, const void *A, cudaDataType Atype, int lda, const void *B, cudaDataType Btype, int ldb, const cuComplex *beta, void *C, cudaDataType Ctype, int ldc) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasCgemm3mEx)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasCgemm3mEx = (cublasStatus_t (*)(cublasHandle_t, cublasOperation_t, cublasOperation_t, int, int, int, const cuComplex *, const void *, cudaDataType, int, const void *, cudaDataType, int, const cuComplex *, void *, cudaDataType, int)) dlsym(libwrapper_handle, "wrapper_cublasCgemm3mEx");
			fprintf(stderr, "wrapper_cublasCgemm3mEx:%p\n", wrapper_cublasCgemm3mEx);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasCgemm3mEx():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasCgemm3mEx(handle, transa, transb, m, n, k, alpha, A, Atype, lda, B, Btype, ldb, beta, C, Ctype, ldc);
		return retval;
	}
}