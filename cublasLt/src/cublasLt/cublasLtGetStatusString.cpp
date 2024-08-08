#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
const char * (*wrapper_cublasLtGetStatusString)(cublasStatus_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	const char * cublasLtGetStatusString(cublasStatus_t status){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtGetStatusString)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtGetStatusString = (const char * (*)(cublasStatus_t)) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtGetStatusString");
			fprintf(stderr, "wrapper_cublasLtGetStatusString:%p\n", wrapper_cublasLtGetStatusString);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtGetStatusString():%s\n", __dlerror);
			fflush(stderr);
		}
		const char * retval = wrapper_cublasLtGetStatusString(status);
		return retval;
	}
}