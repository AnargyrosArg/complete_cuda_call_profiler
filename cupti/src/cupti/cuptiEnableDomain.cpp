#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiEnableDomain)(uint32_t, CUpti_SubscriberHandle, CUpti_CallbackDomain);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiEnableDomain(uint32_t enable, CUpti_SubscriberHandle subscriber, CUpti_CallbackDomain domain) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiEnableDomain)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiEnableDomain = (CUptiResult (*)(uint32_t, CUpti_SubscriberHandle, CUpti_CallbackDomain)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiEnableDomain");
			fprintf(stderr, "wrapper_cuptiEnableDomain:%p\n", wrapper_cuptiEnableDomain);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiEnableDomain():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiEnableDomain(enable, subscriber, domain);
		return retval;
	}
}