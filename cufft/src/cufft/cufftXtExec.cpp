#include <cufftXt.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftXtExec)(cufftHandle, void *, void *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftXtExec(cufftHandle plan, void *input, void *output, int direction) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftXtExec)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftXtExec = (cufftResult (*)(cufftHandle, void *, void *, int)) dlsym(libwrapper_cufft_handle, "wrapper_cufftXtExec");
			fprintf(stderr, "wrapper_cufftXtExec:%p\n", wrapper_cufftXtExec);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftXtExec():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftXtExec(plan, input, output, direction);
		return retval;
	}
}