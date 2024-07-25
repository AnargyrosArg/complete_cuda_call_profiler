#include <cufftXt.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftXtSetGPUs)(cufftHandle, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftXtSetGPUs(cufftHandle handle, int nGPUs, int *whichGPUs) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftXtSetGPUs)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftXtSetGPUs = (cufftResult (*)(cufftHandle, int, int *)) dlsym(libwrapper_cufft_handle, "wrapper_cufftXtSetGPUs");
			fprintf(stderr, "wrapper_cufftXtSetGPUs:%p\n", wrapper_cufftXtSetGPUs);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftXtSetGPUs():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftXtSetGPUs(handle, nGPUs, whichGPUs);
		return retval;
	}
}