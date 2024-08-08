#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasScalEx)(cublasHandle_t, int, const void *, cudaDataType, void *, cudaDataType, int, cudaDataType);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasScalEx(cublasHandle_t handle, int n, const void *alpha, cudaDataType alphaType, void *x, cudaDataType xType, int incx, cudaDataType executionType) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasScalEx)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasScalEx = (cublasStatus_t (*)(cublasHandle_t, int, const void *, cudaDataType, void *, cudaDataType, int, cudaDataType)) dlsym(libwrapper_handle, "wrapper_cublasScalEx");
			fprintf(stderr, "wrapper_cublasScalEx:%p\n", wrapper_cublasScalEx);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasScalEx():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasScalEx(handle, n, alpha, alphaType, x, xType, incx, executionType);
		return retval;
	}
}