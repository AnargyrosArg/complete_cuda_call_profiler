#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasCsyrk_v2)(cublasHandle_t, cublasFillMode_t, cublasOperation_t, int, int, const cuComplex *, const cuComplex *, int, const cuComplex *, cuComplex *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasCsyrk_v2(cublasHandle_t handle, cublasFillMode_t uplo, cublasOperation_t trans, int n, int k, const cuComplex *alpha, const cuComplex *A, int lda, const cuComplex *beta, cuComplex *C, int ldc) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasCsyrk_v2)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasCsyrk_v2 = (cublasStatus_t (*)(cublasHandle_t, cublasFillMode_t, cublasOperation_t, int, int, const cuComplex *, const cuComplex *, int, const cuComplex *, cuComplex *, int)) dlsym(libwrapper_handle, "wrapper_cublasCsyrk_v2");
			fprintf(stderr, "wrapper_cublasCsyrk_v2:%p\n", wrapper_cublasCsyrk_v2);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasCsyrk_v2():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasCsyrk_v2(handle, uplo, trans, n, k, alpha, A, lda, beta, C, ldc);
		return retval;
	}
}