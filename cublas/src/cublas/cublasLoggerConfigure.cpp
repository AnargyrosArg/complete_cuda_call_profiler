#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasLoggerConfigure)(int, int, int, const char *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasLoggerConfigure(int logIsOn, int logToStdOut, int logToStdErr, const char *logFileName) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLoggerConfigure)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLoggerConfigure = (cublasStatus_t (*)(int, int, int, const char *)) dlsym(libwrapper_handle, "wrapper_cublasLoggerConfigure");
			fprintf(stderr, "wrapper_cublasLoggerConfigure:%p\n", wrapper_cublasLoggerConfigure);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLoggerConfigure():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasLoggerConfigure(logIsOn, logToStdOut, logToStdErr, logFileName);
		return retval;
	}
}