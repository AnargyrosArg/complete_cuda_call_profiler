#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasLtDestroy)(cublasLtHandle_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	cublasStatus_t cublasLtDestroy(cublasLtHandle_t lightHandle){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtDestroy)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtDestroy = (cublasStatus_t (*)(cublasLtHandle_t)) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtDestroy");
			fprintf(stderr, "wrapper_cublasLtDestroy:%p\n", wrapper_cublasLtDestroy);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtDestroy():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasLtDestroy(lightHandle);
		return retval;
	}
}