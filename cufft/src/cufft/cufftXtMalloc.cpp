#include <cufftXt.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftXtMalloc)(cufftHandle, cudaLibXtDesc **, cufftXtSubFormat);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftXtMalloc(cufftHandle plan, cudaLibXtDesc **descriptor, cufftXtSubFormat format) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftXtMalloc)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftXtMalloc = (cufftResult (*)(cufftHandle, cudaLibXtDesc **, cufftXtSubFormat)) dlsym(libwrapper_cufft_handle, "wrapper_cufftXtMalloc");
			fprintf(stderr, "wrapper_cufftXtMalloc:%p\n", wrapper_cufftXtMalloc);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftXtMalloc():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftXtMalloc(plan, descriptor, format);
		return retval;
	}
}