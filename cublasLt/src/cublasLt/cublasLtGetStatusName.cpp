#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
const char * (*wrapper_cublasLtGetStatusName)(cublasStatus_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	const char * cublasLtGetStatusName(cublasStatus_t status) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtGetStatusName)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtGetStatusName = (const char * (*)(cublasStatus_t)) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtGetStatusName");
			fprintf(stderr, "wrapper_cublasLtGetStatusName:%p\n", wrapper_cublasLtGetStatusName);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtGetStatusName():%s\n", __dlerror);
			fflush(stderr);
		}
		const char * retval = wrapper_cublasLtGetStatusName(status);
		return retval;
	}
}