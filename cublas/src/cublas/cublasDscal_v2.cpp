#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasDscal_v2)(cublasHandle_t, int, const double *, double *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasDscal_v2(cublasHandle_t handle, int n, const double *alpha, double *x, int incx) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasDscal_v2)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasDscal_v2 = (cublasStatus_t (*)(cublasHandle_t, int, const double *, double *, int)) dlsym(libwrapper_handle, "wrapper_cublasDscal_v2");
			fprintf(stderr, "wrapper_cublasDscal_v2:%p\n", wrapper_cublasDscal_v2);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasDscal_v2():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasDscal_v2(handle, n, alpha, x, incx);
		return retval;
	}
}