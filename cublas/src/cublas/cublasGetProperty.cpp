#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
cublasStatus_t (*wrapper_cublasGetProperty)(libraryPropertyType, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	cublasStatus_t cublasGetProperty(libraryPropertyType type, int *value) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasGetProperty)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasGetProperty = (cublasStatus_t (*)(libraryPropertyType, int *)) dlsym(libwrapper_handle, "wrapper_cublasGetProperty");
			fprintf(stderr, "wrapper_cublasGetProperty:%p\n", wrapper_cublasGetProperty);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasGetProperty():%s\n", __dlerror);
			fflush(stderr);
		}
		cublasStatus_t retval = wrapper_cublasGetProperty(type, value);
		return retval;
	}
}