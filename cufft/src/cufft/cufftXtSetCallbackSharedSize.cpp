#include <cufftXt.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftXtSetCallbackSharedSize)(cufftHandle, cufftXtCallbackType, size_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftXtSetCallbackSharedSize(cufftHandle plan, cufftXtCallbackType cbType, size_t sharedSize){
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftXtSetCallbackSharedSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftXtSetCallbackSharedSize = (cufftResult (*)(cufftHandle, cufftXtCallbackType, size_t)) dlsym(libwrapper_cufft_handle, "wrapper_cufftXtSetCallbackSharedSize");
			fprintf(stderr, "wrapper_cufftXtSetCallbackSharedSize:%p\n", wrapper_cufftXtSetCallbackSharedSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftXtSetCallbackSharedSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftXtSetCallbackSharedSize(plan, cbType, sharedSize);
		return retval;
	}
}