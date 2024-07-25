#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftGetSize)(cufftHandle, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftGetSize(cufftHandle handle, size_t *workSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftGetSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftGetSize = (cufftResult (*)(cufftHandle, size_t *)) dlsym(libwrapper_cufft_handle, "wrapper_cufftGetSize");
			fprintf(stderr, "wrapper_cufftGetSize:%p\n", wrapper_cufftGetSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftGetSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftGetSize(handle, workSize);
		return retval;
	}
}