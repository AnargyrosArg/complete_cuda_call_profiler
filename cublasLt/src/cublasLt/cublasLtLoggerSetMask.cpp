#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasLtLoggerSetMask)(int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	cublasStatus_t cublasLtLoggerSetMask(int mask){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtLoggerSetMask)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtLoggerSetMask = (cublasStatus_t (*)(int)) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtLoggerSetMask");
			fprintf(stderr, "wrapper_cublasLtLoggerSetMask:%p\n", wrapper_cublasLtLoggerSetMask);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtLoggerSetMask():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasLtLoggerSetMask(mask);
		return retval;
	}
}