#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasRotgEx)(cublasHandle_t, void *, void *, cudaDataType, void *, void *, cudaDataType, cudaDataType);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasRotgEx(cublasHandle_t handle, void *a, void *b, cudaDataType abType, void *c, void *s, cudaDataType csType, cudaDataType executiontype) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasRotgEx)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasRotgEx = (cublasStatus_t (*)(cublasHandle_t, void *, void *, cudaDataType, void *, void *, cudaDataType, cudaDataType)) dlsym(libwrapper_handle, "wrapper_cublasRotgEx");
			fprintf(stderr, "wrapper_cublasRotgEx:%p\n", wrapper_cublasRotgEx);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasRotgEx():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasRotgEx(handle, a, b, abType, c, s, csType, executiontype);
		return retval;
	}
}