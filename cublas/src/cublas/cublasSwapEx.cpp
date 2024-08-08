#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasSwapEx)(cublasHandle_t, int, void *, cudaDataType, int, void *, cudaDataType, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasSwapEx(cublasHandle_t handle, int n, void *x, cudaDataType xType, int incx, void *y, cudaDataType yType, int incy) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasSwapEx)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasSwapEx = (cublasStatus_t (*)(cublasHandle_t, int, void *, cudaDataType, int, void *, cudaDataType, int)) dlsym(libwrapper_handle, "wrapper_cublasSwapEx");
			fprintf(stderr, "wrapper_cublasSwapEx:%p\n", wrapper_cublasSwapEx);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasSwapEx():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasSwapEx(handle, n, x, xType, incx, y, yType, incy);
		return retval;
	}
}