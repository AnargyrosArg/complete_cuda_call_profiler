#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasIaminEx)(cublasHandle_t, int, const void *, cudaDataType, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasIaminEx(cublasHandle_t handle, int n, const void *x, cudaDataType xType, int incx, int *result) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasIaminEx)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasIaminEx = (cublasStatus_t (*)(cublasHandle_t, int, const void *, cudaDataType, int, int *)) dlsym(libwrapper_handle, "wrapper_cublasIaminEx");
			fprintf(stderr, "wrapper_cublasIaminEx:%p\n", wrapper_cublasIaminEx);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasIaminEx():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasIaminEx(handle, n, x, xType, incx, result);
		return retval;
	}
}