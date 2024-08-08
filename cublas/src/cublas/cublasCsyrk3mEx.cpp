#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasCsyrk3mEx)(cublasHandle_t, cublasFillMode_t, cublasOperation_t, int, int, const cuComplex *, const void *, cudaDataType, int, const cuComplex *, void *, cudaDataType, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasCsyrk3mEx(cublasHandle_t handle, cublasFillMode_t uplo, cublasOperation_t trans, int n, int k, const cuComplex *alpha, const void *A, cudaDataType Atype, int lda, const cuComplex *beta, void *C, cudaDataType Ctype, int ldc) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasCsyrk3mEx)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasCsyrk3mEx = (cublasStatus_t (*)(cublasHandle_t, cublasFillMode_t, cublasOperation_t, int, int, const cuComplex *, const void *, cudaDataType, int, const cuComplex *, void *, cudaDataType, int)) dlsym(libwrapper_handle, "wrapper_cublasCsyrk3mEx");
			fprintf(stderr, "wrapper_cublasCsyrk3mEx:%p\n", wrapper_cublasCsyrk3mEx);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasCsyrk3mEx():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasCsyrk3mEx(handle, uplo, trans, n, k, alpha, A, Atype, lda, beta, C, Ctype, ldc);
		return retval;
	}
}