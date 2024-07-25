#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftMakePlan2d)(cufftHandle, int, int, cufftType, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftMakePlan2d(cufftHandle plan, int nx, int ny, cufftType type, size_t *workSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftMakePlan2d)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftMakePlan2d = (cufftResult (*)(cufftHandle, int, int, cufftType, size_t *)) dlsym(libwrapper_cufft_handle, "wrapper_cufftMakePlan2d");
			fprintf(stderr, "wrapper_cufftMakePlan2d:%p\n", wrapper_cufftMakePlan2d);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftMakePlan2d():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftMakePlan2d(plan, nx, ny, type, workSize);
		return retval;
	}
}