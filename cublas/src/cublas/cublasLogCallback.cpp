/*#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
void (*wrapper_cublasLogCallback)(const char *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_handle;
extern "C"
{
	void cublasLogCallback(const char *msg) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_handle == NULL){
			libwrapper_handle = dlopen("libwrapper.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cublasLogCallback)
		{
			//fetch the original function addr using dlsym
			wrapper_cublasLogCallback = (void (*)(const char *)) dlsym(libwrapper_handle, "wrapper_cublasLogCallback");
			fprintf(stderr, "wrapper_cublasLogCallback:%p\n", wrapper_cublasLogCallback);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cublasLogCallback():%s\n", __dlerror);
			fflush(stderr);
		}
		wrapper_cublasLogCallback(msg);
	}
}
*/
