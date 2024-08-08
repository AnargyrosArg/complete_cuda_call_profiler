#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiEnableAllDomains)(uint32_t, CUpti_SubscriberHandle);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiEnableAllDomains(uint32_t enable, CUpti_SubscriberHandle subscriber) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiEnableAllDomains)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiEnableAllDomains = (CUptiResult (*)(uint32_t, CUpti_SubscriberHandle)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiEnableAllDomains");
			fprintf(stderr, "wrapper_cuptiEnableAllDomains:%p\n", wrapper_cuptiEnableAllDomains);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiEnableAllDomains():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiEnableAllDomains(enable, subscriber);
		return retval;
	}
}