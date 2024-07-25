#include <cufftXt.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftXtExecDescriptorZ2D)(cufftHandle, cudaLibXtDesc *, cudaLibXtDesc *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftXtExecDescriptorZ2D(cufftHandle plan, cudaLibXtDesc *input, cudaLibXtDesc *output) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftXtExecDescriptorZ2D)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftXtExecDescriptorZ2D = (cufftResult (*)(cufftHandle, cudaLibXtDesc *, cudaLibXtDesc *)) dlsym(libwrapper_cufft_handle, "wrapper_cufftXtExecDescriptorZ2D");
			fprintf(stderr, "wrapper_cufftXtExecDescriptorZ2D:%p\n", wrapper_cufftXtExecDescriptorZ2D);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftXtExecDescriptorZ2D():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftXtExecDescriptorZ2D(plan, input, output);
		return retval;
	}
}