#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasDtbmv_v2)(cublasHandle_t, cublasFillMode_t, cublasOperation_t, cublasDiagType_t, int, int, const double *, int, double *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasDtbmv_v2(cublasHandle_t handle, cublasFillMode_t uplo, cublasOperation_t trans, cublasDiagType_t diag, int n, int k, const double *A, int lda, double *x, int incx) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasDtbmv_v2)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasDtbmv_v2 = (cublasStatus_t (*)(cublasHandle_t, cublasFillMode_t, cublasOperation_t, cublasDiagType_t, int, int, const double *, int, double *, int)) dlsym(libwrapper_handle, "wrapper_cublasDtbmv_v2");
			fprintf(stderr, "wrapper_cublasDtbmv_v2:%p\n", wrapper_cublasDtbmv_v2);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasDtbmv_v2():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasDtbmv_v2(handle, uplo, trans, diag, n, k, A, lda, x, incx);
		return retval;
	}
}