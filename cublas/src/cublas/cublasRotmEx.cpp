#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasRotmEx)(cublasHandle_t, int, void *, cudaDataType, int, void *, cudaDataType, int, const void *, cudaDataType, cudaDataType);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasRotmEx(cublasHandle_t handle, int n, void *x, cudaDataType xType, int incx, void *y, cudaDataType yType, int incy, const void *param, cudaDataType paramType, cudaDataType executiontype) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasRotmEx)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasRotmEx = (cublasStatus_t (*)(cublasHandle_t, int, void *, cudaDataType, int, void *, cudaDataType, int, const void *, cudaDataType, cudaDataType)) dlsym(libwrapper_handle, "wrapper_cublasRotmEx");
			fprintf(stderr, "wrapper_cublasRotmEx:%p\n", wrapper_cublasRotmEx);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasRotmEx():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasRotmEx(handle, n, x, xType, incx, y, yType, incy, param, paramType, executiontype);
		return retval;
	}
}