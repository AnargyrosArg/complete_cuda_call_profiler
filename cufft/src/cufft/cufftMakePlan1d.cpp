#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftMakePlan1d)(cufftHandle, int, cufftType, int, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftMakePlan1d(cufftHandle plan, int nx, cufftType type, int batch, size_t *workSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftMakePlan1d)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftMakePlan1d = (cufftResult (*)(cufftHandle, int, cufftType, int, size_t *)) dlsym(libwrapper_cufft_handle, "wrapper_cufftMakePlan1d");
			fprintf(stderr, "wrapper_cufftMakePlan1d:%p\n", wrapper_cufftMakePlan1d);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftMakePlan1d():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftMakePlan1d(plan, nx, type, batch, workSize);
		return retval;
	}
}