#include <cufftXt.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftXtClearCallback)(cufftHandle, cufftXtCallbackType);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftXtClearCallback(cufftHandle plan, cufftXtCallbackType cbType){
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftXtClearCallback)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftXtClearCallback = (cufftResult (*)(cufftHandle, cufftXtCallbackType)) dlsym(libwrapper_cufft_handle, "wrapper_cufftXtClearCallback");
			fprintf(stderr, "wrapper_cufftXtClearCallback:%p\n", wrapper_cufftXtClearCallback);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftXtClearCallback():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftXtClearCallback(plan, cbType);
		return retval;
	}
}