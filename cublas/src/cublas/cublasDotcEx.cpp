#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasDotcEx)(cublasHandle_t, int, const void *, cudaDataType, int, const void *, cudaDataType, int, void *, cudaDataType, cudaDataType);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasDotcEx(cublasHandle_t handle, int n, const void *x, cudaDataType xType, int incx, const void *y, cudaDataType yType, int incy, void *result, cudaDataType resultType, cudaDataType executionType) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasDotcEx)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasDotcEx = (cublasStatus_t (*)(cublasHandle_t, int, const void *, cudaDataType, int, const void *, cudaDataType, int, void *, cudaDataType, cudaDataType)) dlsym(libwrapper_handle, "wrapper_cublasDotcEx");
			fprintf(stderr, "wrapper_cublasDotcEx:%p\n", wrapper_cublasDotcEx);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasDotcEx():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasDotcEx(handle, n, x, xType, incx, y, yType, incy, result, resultType, executionType);
		return retval;
	}
}