#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasLtLoggerForceDisable)();
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	cublasStatus_t cublasLtLoggerForceDisable() {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtLoggerForceDisable)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtLoggerForceDisable = (cublasStatus_t (*)()) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtLoggerForceDisable");
			fprintf(stderr, "wrapper_cublasLtLoggerForceDisable:%p\n", wrapper_cublasLtLoggerForceDisable);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtLoggerForceDisable():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasLtLoggerForceDisable();
		return retval;
	}
}