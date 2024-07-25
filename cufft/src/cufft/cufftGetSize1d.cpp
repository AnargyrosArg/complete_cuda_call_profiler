#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftGetSize1d)(cufftHandle, int, cufftType, int, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftGetSize1d(cufftHandle handle, int nx, cufftType type, int batch, size_t *workSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftGetSize1d)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftGetSize1d = (cufftResult (*)(cufftHandle, int, cufftType, int, size_t *)) dlsym(libwrapper_cufft_handle, "wrapper_cufftGetSize1d");
			fprintf(stderr, "wrapper_cufftGetSize1d:%p\n", wrapper_cufftGetSize1d);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftGetSize1d():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftGetSize1d(handle, nx, type, batch, workSize);
		return retval;
	}
}