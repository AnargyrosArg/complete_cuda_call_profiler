#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiUnsubscribe)(CUpti_SubscriberHandle);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiUnsubscribe(CUpti_SubscriberHandle subscriber) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiUnsubscribe)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiUnsubscribe = (CUptiResult (*)(CUpti_SubscriberHandle)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiUnsubscribe");
			fprintf(stderr, "wrapper_cuptiUnsubscribe:%p\n", wrapper_cuptiUnsubscribe);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiUnsubscribe():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiUnsubscribe(subscriber);
		return retval;
	}
}