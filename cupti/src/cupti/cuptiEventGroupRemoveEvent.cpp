#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiEventGroupRemoveEvent)(CUpti_EventGroup, CUpti_EventID);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiEventGroupRemoveEvent(CUpti_EventGroup eventGroup, CUpti_EventID event) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiEventGroupRemoveEvent)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiEventGroupRemoveEvent = (CUptiResult (*)(CUpti_EventGroup, CUpti_EventID)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiEventGroupRemoveEvent");
			fprintf(stderr, "wrapper_cuptiEventGroupRemoveEvent:%p\n", wrapper_cuptiEventGroupRemoveEvent);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiEventGroupRemoveEvent():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiEventGroupRemoveEvent(eventGroup, event);
		return retval;
	}
}