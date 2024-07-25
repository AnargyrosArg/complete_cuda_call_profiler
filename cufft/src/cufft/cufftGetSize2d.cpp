#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftGetSize2d)(cufftHandle, int, int, cufftType, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftGetSize2d(cufftHandle handle, int nx, int ny, cufftType type, size_t *workSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftGetSize2d)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftGetSize2d = (cufftResult (*)(cufftHandle, int, int, cufftType, size_t *)) dlsym(libwrapper_cufft_handle, "wrapper_cufftGetSize2d");
			fprintf(stderr, "wrapper_cufftGetSize2d:%p\n", wrapper_cufftGetSize2d);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftGetSize2d():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftGetSize2d(handle, nx, ny, type, workSize);
		return retval;
	}
}