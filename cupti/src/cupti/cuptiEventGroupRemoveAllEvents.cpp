#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiEventGroupRemoveAllEvents)(CUpti_EventGroup);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiEventGroupRemoveAllEvents(CUpti_EventGroup eventGroup) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiEventGroupRemoveAllEvents)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiEventGroupRemoveAllEvents = (CUptiResult (*)(CUpti_EventGroup)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiEventGroupRemoveAllEvents");
			fprintf(stderr, "wrapper_cuptiEventGroupRemoveAllEvents:%p\n", wrapper_cuptiEventGroupRemoveAllEvents);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiEventGroupRemoveAllEvents():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiEventGroupRemoveAllEvents(eventGroup);
		return retval;
	}
}