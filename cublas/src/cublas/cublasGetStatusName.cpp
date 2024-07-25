#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
const char * (*wrapper_cublasGetStatusName)(cublasStatus_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	const char * cublasGetStatusName(cublasStatus_t status) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasGetStatusName)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasGetStatusName = (const char * (*)(cublasStatus_t)) dlsym(libwrapper_handle, "wrapper_cublasGetStatusName");
			fprintf(stderr, "wrapper_cublasGetStatusName:%p\n", wrapper_cublasGetStatusName);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasGetStatusName():%s\n", __dlerror);
			fflush(stderr);
		}
		const char * retval = wrapper_cublasGetStatusName(status);
		return retval;
	}
}