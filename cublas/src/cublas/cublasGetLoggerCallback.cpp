/*#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasGetLoggerCallback)(cublasLogCallback *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasGetLoggerCallback(cublasLogCallback *userCallback) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasGetLoggerCallback)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasGetLoggerCallback = (cublasStatus_t (*)(cublasLogCallback *)) dlsym(libwrapper_handle, "wrapper_cublasGetLoggerCallback");
			fprintf(stderr, "wrapper_cublasGetLoggerCallback:%p\n", wrapper_cublasGetLoggerCallback);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasGetLoggerCallback():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasGetLoggerCallback(userCallback);
		return retval;
	}
}
*/
