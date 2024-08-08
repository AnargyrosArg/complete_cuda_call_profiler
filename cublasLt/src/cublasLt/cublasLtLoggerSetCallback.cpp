#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasLtLoggerSetCallback)(cublasLtLoggerCallback_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	cublasStatus_t cublasLtLoggerSetCallback(cublasLtLoggerCallback_t callback){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtLoggerSetCallback)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtLoggerSetCallback = (cublasStatus_t (*)(cublasLtLoggerCallback_t)) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtLoggerSetCallback");
			fprintf(stderr, "wrapper_cublasLtLoggerSetCallback:%p\n", wrapper_cublasLtLoggerSetCallback);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtLoggerSetCallback():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasLtLoggerSetCallback(callback);
		return retval;
	}
}