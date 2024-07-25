#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasCopyEx)(cublasHandle_t, int, const void *, cudaDataType, int, void *, cudaDataType, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasCopyEx(cublasHandle_t handle, int n, const void *x, cudaDataType xType, int incx, void *y, cudaDataType yType, int incy) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasCopyEx)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasCopyEx = (cublasStatus_t (*)(cublasHandle_t, int, const void *, cudaDataType, int, void *, cudaDataType, int)) dlsym(libwrapper_handle, "wrapper_cublasCopyEx");
			fprintf(stderr, "wrapper_cublasCopyEx:%p\n", wrapper_cublasCopyEx);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasCopyEx():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasCopyEx(handle, n, x, xType, incx, y, yType, incy);
		return retval;
	}
}