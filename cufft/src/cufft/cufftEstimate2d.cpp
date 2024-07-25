#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftEstimate2d)(int, int, cufftType, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftEstimate2d(int nx, int ny, cufftType type, size_t *workSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftEstimate2d)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftEstimate2d = (cufftResult (*)(int, int, cufftType, size_t *)) dlsym(libwrapper_cufft_handle, "wrapper_cufftEstimate2d");
			fprintf(stderr, "wrapper_cufftEstimate2d:%p\n", wrapper_cufftEstimate2d);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftEstimate2d():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftEstimate2d(nx, ny, type, workSize);
		return retval;
	}
}