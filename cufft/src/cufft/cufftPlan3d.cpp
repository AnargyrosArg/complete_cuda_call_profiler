#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftPlan3d)(cufftHandle *, int, int, int, cufftType);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftPlan3d(cufftHandle *plan, int nx, int ny, int nz, cufftType type) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftPlan3d)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftPlan3d = (cufftResult (*)(cufftHandle *, int, int, int, cufftType)) dlsym(libwrapper_cufft_handle, "wrapper_cufftPlan3d");
			fprintf(stderr, "wrapper_cufftPlan3d:%p\n", wrapper_cufftPlan3d);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftPlan3d():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftPlan3d(plan, nx, ny, nz, type);
		return retval;
	}
}