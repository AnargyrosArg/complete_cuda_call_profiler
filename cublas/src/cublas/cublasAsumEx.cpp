#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasAsumEx)(cublasHandle_t, int, const void *, cudaDataType, int, void *, cudaDataType, cudaDataType);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasAsumEx(cublasHandle_t handle, int n, const void *x, cudaDataType xType, int incx, void *result, cudaDataType resultType, cudaDataType executiontype) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasAsumEx)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasAsumEx = (cublasStatus_t (*)(cublasHandle_t, int, const void *, cudaDataType, int, void *, cudaDataType, cudaDataType)) dlsym(libwrapper_handle, "wrapper_cublasAsumEx");
			fprintf(stderr, "wrapper_cublasAsumEx:%p\n", wrapper_cublasAsumEx);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasAsumEx():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasAsumEx(handle, n, x, xType, incx, result, resultType, executiontype);
		return retval;
	}
}