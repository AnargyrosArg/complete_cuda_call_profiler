#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
size_t (*wrapper_cublasLtGetCudartVersion)();
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	size_t cublasLtGetCudartVersion(){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtGetCudartVersion)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtGetCudartVersion = (size_t (*)()) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtGetCudartVersion");
			fprintf(stderr, "wrapper_cublasLtGetCudartVersion:%p\n", wrapper_cublasLtGetCudartVersion);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtGetCudartVersion():%s\n", __dlerror);
			fflush(stderr);
		}
		size_t retval = wrapper_cublasLtGetCudartVersion();
		return retval;
	}
}