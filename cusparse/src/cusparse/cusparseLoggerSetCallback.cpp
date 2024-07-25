#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseLoggerSetCallback)(cusparseLoggerCallback_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseLoggerSetCallback(cusparseLoggerCallback_t callback) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseLoggerSetCallback)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseLoggerSetCallback = (cusparseStatus_t (*)(cusparseLoggerCallback_t)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseLoggerSetCallback");
			fprintf(stderr, "wrapper_cusparseLoggerSetCallback:%p\n", wrapper_cusparseLoggerSetCallback);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseLoggerSetCallback():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseLoggerSetCallback(callback);
		return retval;
	}
}