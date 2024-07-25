#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftCreate)(cufftHandle *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftCreate(cufftHandle *handle) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftCreate)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftCreate = (cufftResult (*)(cufftHandle *)) dlsym(libwrapper_cufft_handle, "wrapper_cufftCreate");
			fprintf(stderr, "wrapper_cufftCreate:%p\n", wrapper_cufftCreate);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftCreate():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftCreate(handle);
		return retval;
	}
}