#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiEventGroupAddEvent)(CUpti_EventGroup, CUpti_EventID);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiEventGroupAddEvent(CUpti_EventGroup eventGroup, CUpti_EventID event) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiEventGroupAddEvent)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiEventGroupAddEvent = (CUptiResult (*)(CUpti_EventGroup, CUpti_EventID)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiEventGroupAddEvent");
			fprintf(stderr, "wrapper_cuptiEventGroupAddEvent:%p\n", wrapper_cuptiEventGroupAddEvent);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiEventGroupAddEvent():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiEventGroupAddEvent(eventGroup, event);
		return retval;
	}
}