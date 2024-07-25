#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasLtLoggerOpenFile)(const char *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	cublasStatus_t cublasLtLoggerOpenFile(const char *logFile) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtLoggerOpenFile)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtLoggerOpenFile = (cublasStatus_t (*)(const char *)) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtLoggerOpenFile");
			fprintf(stderr, "wrapper_cublasLtLoggerOpenFile:%p\n", wrapper_cublasLtLoggerOpenFile);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtLoggerOpenFile():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasLtLoggerOpenFile(logFile);
		return retval;
	}
}