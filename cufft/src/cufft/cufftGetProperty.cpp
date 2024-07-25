#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftGetProperty)(libraryPropertyType, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftGetProperty(libraryPropertyType type, int *value) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftGetProperty)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftGetProperty = (cufftResult (*)(libraryPropertyType, int *)) dlsym(libwrapper_cufft_handle, "wrapper_cufftGetProperty");
			fprintf(stderr, "wrapper_cufftGetProperty:%p\n", wrapper_cufftGetProperty);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftGetProperty():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftGetProperty(type, value);
		return retval;
	}
}