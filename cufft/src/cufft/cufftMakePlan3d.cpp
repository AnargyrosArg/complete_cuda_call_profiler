#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftMakePlan3d)(cufftHandle, int, int, int, cufftType, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftMakePlan3d(cufftHandle plan, int nx, int ny, int nz, cufftType type, size_t *workSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftMakePlan3d)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftMakePlan3d = (cufftResult (*)(cufftHandle, int, int, int, cufftType, size_t *)) dlsym(libwrapper_cufft_handle, "wrapper_cufftMakePlan3d");
			fprintf(stderr, "wrapper_cufftMakePlan3d:%p\n", wrapper_cufftMakePlan3d);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftMakePlan3d():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftMakePlan3d(plan, nx, ny, nz, type, workSize);
		return retval;
	}
}