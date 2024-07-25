#include <cublasLt.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasLtGetProperty)(libraryPropertyType, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cublasLt_handle;
extern "C"
{
	cublasStatus_t cublasLtGetProperty(libraryPropertyType type, int *value) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cublasLt_handle == NULL){
			libwrapper_cublasLt_handle = dlopen("libwrapper_cublasLt.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLtGetProperty)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLtGetProperty = (cublasStatus_t (*)(libraryPropertyType, int *)) dlsym(libwrapper_cublasLt_handle, "wrapper_cublasLtGetProperty");
			fprintf(stderr, "wrapper_cublasLtGetProperty:%p\n", wrapper_cublasLtGetProperty);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLtGetProperty():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasLtGetProperty(type, value);
		return retval;
	}
}