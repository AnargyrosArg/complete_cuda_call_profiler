#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
size_t (*wrapper_cublasLtGetVersion)();
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	size_t cublasLtGetVersion(){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtGetVersion)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtGetVersion = (size_t (*)()) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtGetVersion");
			fprintf(stderr, "wrapper_cublasLtGetVersion:%p\n", wrapper_cublasLtGetVersion);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtGetVersion():%s\n", __dlerror);
			fflush(stderr);
		}
		size_t retval = wrapper_cublasLtGetVersion();
		return retval;
	}
}