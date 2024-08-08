#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasGetMathMode)(cublasHandle_t, cublasMath_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasGetMathMode(cublasHandle_t handle, cublasMath_t *mode) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasGetMathMode)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasGetMathMode = (cublasStatus_t (*)(cublasHandle_t, cublasMath_t *)) dlsym(libwrapper_handle, "wrapper_cublasGetMathMode");
			fprintf(stderr, "wrapper_cublasGetMathMode:%p\n", wrapper_cublasGetMathMode);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasGetMathMode():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasGetMathMode(handle, mode);
		return retval;
	}
}