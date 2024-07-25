#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasSrotm_v2)(cublasHandle_t, int, float *, int, float *, int, const float *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasSrotm_v2(cublasHandle_t handle, int n, float *x, int incx, float *y, int incy, const float *param) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasSrotm_v2)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasSrotm_v2 = (cublasStatus_t (*)(cublasHandle_t, int, float *, int, float *, int, const float *)) dlsym(libwrapper_handle, "wrapper_cublasSrotm_v2");
			fprintf(stderr, "wrapper_cublasSrotm_v2:%p\n", wrapper_cublasSrotm_v2);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasSrotm_v2():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasSrotm_v2(handle, n, x, incx, y, incy, param);
		return retval;
	}
}