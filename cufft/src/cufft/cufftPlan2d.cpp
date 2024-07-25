#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftPlan2d)(cufftHandle *, int, int, cufftType);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftPlan2d(cufftHandle *plan, int nx, int ny, cufftType type) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftPlan2d)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftPlan2d = (cufftResult (*)(cufftHandle *, int, int, cufftType)) dlsym(libwrapper_cufft_handle, "wrapper_cufftPlan2d");
			fprintf(stderr, "wrapper_cufftPlan2d:%p\n", wrapper_cufftPlan2d);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftPlan2d():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftPlan2d(plan, nx, ny, type);
		return retval;
	}
}