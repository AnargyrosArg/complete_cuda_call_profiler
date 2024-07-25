#include <cufftXt.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftXtFree)(cudaLibXtDesc *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftXtFree(cudaLibXtDesc *descriptor) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftXtFree)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftXtFree = (cufftResult (*)(cudaLibXtDesc *)) dlsym(libwrapper_cufft_handle, "wrapper_cufftXtFree");
			fprintf(stderr, "wrapper_cufftXtFree:%p\n", wrapper_cufftXtFree);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftXtFree():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftXtFree(descriptor);
		return retval;
	}
}