#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasDotEx)(cublasHandle_t, int, const void *, cudaDataType, int, const void *, cudaDataType, int, void *, cudaDataType, cudaDataType);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasDotEx(cublasHandle_t handle, int n, const void *x, cudaDataType xType, int incx, const void *y, cudaDataType yType, int incy, void *result, cudaDataType resultType, cudaDataType executionType) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasDotEx)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasDotEx = (cublasStatus_t (*)(cublasHandle_t, int, const void *, cudaDataType, int, const void *, cudaDataType, int, void *, cudaDataType, cudaDataType)) dlsym(libwrapper_handle, "wrapper_cublasDotEx");
			fprintf(stderr, "wrapper_cublasDotEx:%p\n", wrapper_cublasDotEx);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasDotEx():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasDotEx(handle, n, x, xType, incx, y, yType, incy, result, resultType, executionType);
		return retval;
	}
}