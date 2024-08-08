#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasZhpr_v2)(cublasHandle_t, cublasFillMode_t, int, const double *, const cuDoubleComplex *, int, cuDoubleComplex *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasZhpr_v2(cublasHandle_t handle, cublasFillMode_t uplo, int n, const double *alpha, const cuDoubleComplex *x, int incx, cuDoubleComplex *AP) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasZhpr_v2)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasZhpr_v2 = (cublasStatus_t (*)(cublasHandle_t, cublasFillMode_t, int, const double *, const cuDoubleComplex *, int, cuDoubleComplex *)) dlsym(libwrapper_handle, "wrapper_cublasZhpr_v2");
			fprintf(stderr, "wrapper_cublasZhpr_v2:%p\n", wrapper_cublasZhpr_v2);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasZhpr_v2():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasZhpr_v2(handle, uplo, n, alpha, x, incx, AP);
		return retval;
	}
}