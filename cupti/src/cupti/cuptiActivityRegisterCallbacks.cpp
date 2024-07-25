#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiActivityRegisterCallbacks)(CUpti_BuffersCallbackRequestFunc, CUpti_BuffersCallbackCompleteFunc);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiActivityRegisterCallbacks(CUpti_BuffersCallbackRequestFunc funcBufferRequested, CUpti_BuffersCallbackCompleteFunc funcBufferCompleted) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiActivityRegisterCallbacks)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiActivityRegisterCallbacks = (CUptiResult (*)(CUpti_BuffersCallbackRequestFunc, CUpti_BuffersCallbackCompleteFunc)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiActivityRegisterCallbacks");
			fprintf(stderr, "wrapper_cuptiActivityRegisterCallbacks:%p\n", wrapper_cuptiActivityRegisterCallbacks);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiActivityRegisterCallbacks():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiActivityRegisterCallbacks(funcBufferRequested, funcBufferCompleted);
		return retval;
	}
}