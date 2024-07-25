#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasSger_v2)(cublasHandle_t, int, int, const float *, const float *, int, const float *, int, float *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasSger_v2(cublasHandle_t handle, int m, int n, const float *alpha, const float *x, int incx, const float *y, int incy, float *A, int lda) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasSger_v2)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasSger_v2 = (cublasStatus_t (*)(cublasHandle_t, int, int, const float *, const float *, int, const float *, int, float *, int)) dlsym(libwrapper_handle, "wrapper_cublasSger_v2");
			fprintf(stderr, "wrapper_cublasSger_v2:%p\n", wrapper_cublasSger_v2);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasSger_v2():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasSger_v2(handle, m, n, alpha, x, incx, y, incy, A, lda);
		return retval;
	}
}