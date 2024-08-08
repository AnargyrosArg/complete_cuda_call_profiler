#include <cufftXt.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftXtSetCallback)(cufftHandle, void **, cufftXtCallbackType, void **);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftXtSetCallback(cufftHandle plan, void **callback_routine, cufftXtCallbackType cbType, void **caller_info){
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftXtSetCallback)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftXtSetCallback = (cufftResult (*)(cufftHandle, void **, cufftXtCallbackType, void **)) dlsym(libwrapper_cufft_handle, "wrapper_cufftXtSetCallback");
			fprintf(stderr, "wrapper_cufftXtSetCallback:%p\n", wrapper_cufftXtSetCallback);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftXtSetCallback():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftXtSetCallback(plan, callback_routine, cbType, caller_info);
		return retval;
	}
}