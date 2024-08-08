#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
const char * (*wrapper_cublasGetStatusString)(cublasStatus_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	const char * cublasGetStatusString(cublasStatus_t status) {
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasGetStatusString)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasGetStatusString = (const char * (*)(cublasStatus_t)) dlsym(libwrapper_handle, "wrapper_cublasGetStatusString");
			fprintf(stderr, "wrapper_cublasGetStatusString:%p\n", wrapper_cublasGetStatusString);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasGetStatusString():%s\n", __dlerror);
			fflush(stderr);
		}
		const char * retval = wrapper_cublasGetStatusString(status);
		return retval;
	}
}