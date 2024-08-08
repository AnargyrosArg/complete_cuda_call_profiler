#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasDger_v2)(cublasHandle_t, int, int, const double *, const double *, int, const double *, int, double *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasDger_v2(cublasHandle_t handle, int m, int n, const double *alpha, const double *x, int incx, const double *y, int incy, double *A, int lda) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasDger_v2)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasDger_v2 = (cublasStatus_t (*)(cublasHandle_t, int, int, const double *, const double *, int, const double *, int, double *, int)) dlsym(libwrapper_handle, "wrapper_cublasDger_v2");
			fprintf(stderr, "wrapper_cublasDger_v2:%p\n", wrapper_cublasDger_v2);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasDger_v2():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasDger_v2(handle, m, n, alpha, x, incx, y, incy, A, lda);
		return retval;
	}
}