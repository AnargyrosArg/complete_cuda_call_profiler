#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
size_t (*wrapper_cublasGetCudartVersion)();
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	size_t cublasGetCudartVersion() {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasGetCudartVersion)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasGetCudartVersion = (size_t (*)()) dlsym(libwrapper_handle, "wrapper_cublasGetCudartVersion");
			fprintf(stderr, "wrapper_cublasGetCudartVersion:%p\n", wrapper_cublasGetCudartVersion);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasGetCudartVersion():%s\n", __dlerror);
			fflush(stderr);
		}
		size_t retval = wrapper_cublasGetCudartVersion();
		return retval;
	}
}