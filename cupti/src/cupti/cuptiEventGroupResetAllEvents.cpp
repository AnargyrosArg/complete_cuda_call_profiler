#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiEventGroupResetAllEvents)(CUpti_EventGroup);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiEventGroupResetAllEvents(CUpti_EventGroup eventGroup) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiEventGroupResetAllEvents)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiEventGroupResetAllEvents = (CUptiResult (*)(CUpti_EventGroup)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiEventGroupResetAllEvents");
			fprintf(stderr, "wrapper_cuptiEventGroupResetAllEvents:%p\n", wrapper_cuptiEventGroupResetAllEvents);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiEventGroupResetAllEvents():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiEventGroupResetAllEvents(eventGroup);
		return retval;
	}
}