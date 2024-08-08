#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiSubscribe)(CUpti_SubscriberHandle *, CUpti_CallbackFunc, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiSubscribe(CUpti_SubscriberHandle *subscriber, CUpti_CallbackFunc callback, void *userdata) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiSubscribe)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiSubscribe = (CUptiResult (*)(CUpti_SubscriberHandle *, CUpti_CallbackFunc, void *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiSubscribe");
			fprintf(stderr, "wrapper_cuptiSubscribe:%p\n", wrapper_cuptiSubscribe);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiSubscribe():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiSubscribe(subscriber, callback, userdata);
		return retval;
	}
}