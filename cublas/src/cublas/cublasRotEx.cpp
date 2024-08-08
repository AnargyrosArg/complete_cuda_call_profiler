#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasRotEx)(cublasHandle_t, int, void *, cudaDataType, int, void *, cudaDataType, int, const void *, const void *, cudaDataType, cudaDataType);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasRotEx(cublasHandle_t handle, int n, void *x, cudaDataType xType, int incx, void *y, cudaDataType yType, int incy, const void *c, const void *s, cudaDataType csType, cudaDataType executiontype) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasRotEx)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasRotEx = (cublasStatus_t (*)(cublasHandle_t, int, void *, cudaDataType, int, void *, cudaDataType, int, const void *, const void *, cudaDataType, cudaDataType)) dlsym(libwrapper_handle, "wrapper_cublasRotEx");
			fprintf(stderr, "wrapper_cublasRotEx:%p\n", wrapper_cublasRotEx);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasRotEx():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasRotEx(handle, n, x, xType, incx, y, yType, incy, c, s, csType, executiontype);
		return retval;
	}
}