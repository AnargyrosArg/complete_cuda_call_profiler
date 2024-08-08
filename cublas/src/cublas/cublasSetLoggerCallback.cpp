/*#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasSetLoggerCallback)(cublasLogCallback);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasSetLoggerCallback(cublasLogCallback userCallback) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasSetLoggerCallback)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasSetLoggerCallback = (cublasStatus_t (*)(cublasLogCallback)) dlsym(libwrapper_handle, "wrapper_cublasSetLoggerCallback");
			fprintf(stderr, "wrapper_cublasSetLoggerCallback:%p\n", wrapper_cublasSetLoggerCallback);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasSetLoggerCallback():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasSetLoggerCallback(userCallback);
		return retval;
	}
}
*/
