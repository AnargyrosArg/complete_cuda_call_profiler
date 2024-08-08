#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasAxpyEx)(cublasHandle_t, int, const void *, cudaDataType, const void *, cudaDataType, int, void *, cudaDataType, int, cudaDataType);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasAxpyEx(cublasHandle_t handle, int n, const void *alpha, cudaDataType alphaType, const void *x, cudaDataType xType, int incx, void *y, cudaDataType yType, int incy, cudaDataType executiontype) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasAxpyEx)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasAxpyEx = (cublasStatus_t (*)(cublasHandle_t, int, const void *, cudaDataType, const void *, cudaDataType, int, void *, cudaDataType, int, cudaDataType)) dlsym(libwrapper_handle, "wrapper_cublasAxpyEx");
			fprintf(stderr, "wrapper_cublasAxpyEx:%p\n", wrapper_cublasAxpyEx);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasAxpyEx():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasAxpyEx(handle, n, alpha, alphaType, x, xType, incx, y, yType, incy, executiontype);
		return retval;
	}
}