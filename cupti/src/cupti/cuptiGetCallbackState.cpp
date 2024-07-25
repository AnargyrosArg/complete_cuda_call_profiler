#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiGetCallbackState)(uint32_t *, CUpti_SubscriberHandle, CUpti_CallbackDomain, CUpti_CallbackId);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiGetCallbackState(uint32_t *enable, CUpti_SubscriberHandle subscriber, CUpti_CallbackDomain domain, CUpti_CallbackId cbid) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiGetCallbackState)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiGetCallbackState = (CUptiResult (*)(uint32_t *, CUpti_SubscriberHandle, CUpti_CallbackDomain, CUpti_CallbackId)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiGetCallbackState");
			fprintf(stderr, "wrapper_cuptiGetCallbackState:%p\n", wrapper_cuptiGetCallbackState);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiGetCallbackState():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiGetCallbackState(enable, subscriber, domain, cbid);
		return retval;
	}
}