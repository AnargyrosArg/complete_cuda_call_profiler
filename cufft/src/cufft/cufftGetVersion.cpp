#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftGetVersion)(int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftGetVersion(int *version){
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftGetVersion)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftGetVersion = (cufftResult (*)(int *)) dlsym(libwrapper_cufft_handle, "wrapper_cufftGetVersion");
			fprintf(stderr, "wrapper_cufftGetVersion:%p\n", wrapper_cufftGetVersion);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftGetVersion():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftGetVersion(version);
		return retval;
	}
}