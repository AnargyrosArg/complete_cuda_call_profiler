#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasIcamin_v2)(cublasHandle_t, int, const cuComplex *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasIcamin_v2(cublasHandle_t handle, int n, const cuComplex *x, int incx, int *result) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasIcamin_v2)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasIcamin_v2 = (cublasStatus_t (*)(cublasHandle_t, int, const cuComplex *, int, int *)) dlsym(libwrapper_handle, "wrapper_cublasIcamin_v2");
			fprintf(stderr, "wrapper_cublasIcamin_v2:%p\n", wrapper_cublasIcamin_v2);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasIcamin_v2():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasIcamin_v2(handle, n, x, incx, result);
		return retval;
	}
}