#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasDsyrk_v2)(cublasHandle_t, cublasFillMode_t, cublasOperation_t, int, int, const double *, const double *, int, const double *, double *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasDsyrk_v2(cublasHandle_t handle, cublasFillMode_t uplo, cublasOperation_t trans, int n, int k, const double *alpha, const double *A, int lda, const double *beta, double *C, int ldc) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasDsyrk_v2)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasDsyrk_v2 = (cublasStatus_t (*)(cublasHandle_t, cublasFillMode_t, cublasOperation_t, int, int, const double *, const double *, int, const double *, double *, int)) dlsym(libwrapper_handle, "wrapper_cublasDsyrk_v2");
			fprintf(stderr, "wrapper_cublasDsyrk_v2:%p\n", wrapper_cublasDsyrk_v2);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasDsyrk_v2():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasDsyrk_v2(handle, uplo, trans, n, k, alpha, A, lda, beta, C, ldc);
		return retval;
	}
}