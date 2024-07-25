#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasSetVector)(int, int, const void *, int, void *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasSetVector(int n, int elemSize, const void *x, int incx, void *devicePtr, int incy) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasSetVector)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasSetVector = (cublasStatus_t (*)(int, int, const void *, int, void *, int)) dlsym(libwrapper_handle, "wrapper_cublasSetVector");
			fprintf(stderr, "wrapper_cublasSetVector:%p\n", wrapper_cublasSetVector);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasSetVector():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasSetVector(n, elemSize, x, incx, devicePtr, incy);
		return retval;
	}
}