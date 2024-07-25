#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiEnableCallback)(uint32_t, CUpti_SubscriberHandle, CUpti_CallbackDomain, CUpti_CallbackId);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiEnableCallback(uint32_t enable, CUpti_SubscriberHandle subscriber, CUpti_CallbackDomain domain, CUpti_CallbackId cbid) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiEnableCallback)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiEnableCallback = (CUptiResult (*)(uint32_t, CUpti_SubscriberHandle, CUpti_CallbackDomain, CUpti_CallbackId)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiEnableCallback");
			fprintf(stderr, "wrapper_cuptiEnableCallback:%p\n", wrapper_cuptiEnableCallback);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiEnableCallback():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiEnableCallback(enable, subscriber, domain, cbid);
		return retval;
	}
}