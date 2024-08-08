#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasDgbmv_v2)(cublasHandle_t, cublasOperation_t, int, int, int, int, const double *, const double *, int, const double *, int, const double *, double *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasDgbmv_v2(cublasHandle_t handle, cublasOperation_t trans, int m, int n, int kl, int ku, const double *alpha, const double *A, int lda, const double *x, int incx, const double *beta, double *y, int incy) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasDgbmv_v2)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasDgbmv_v2 = (cublasStatus_t (*)(cublasHandle_t, cublasOperation_t, int, int, int, int, const double *, const double *, int, const double *, int, const double *, double *, int)) dlsym(libwrapper_handle, "wrapper_cublasDgbmv_v2");
			fprintf(stderr, "wrapper_cublasDgbmv_v2:%p\n", wrapper_cublasDgbmv_v2);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasDgbmv_v2():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasDgbmv_v2(handle, trans, m, n, kl, ku, alpha, A, lda, x, incx, beta, y, incy);
		return retval;
	}
}