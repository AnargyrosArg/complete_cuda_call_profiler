#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiEventDomainGetNumEvents)(CUpti_EventDomainID, uint32_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiEventDomainGetNumEvents(CUpti_EventDomainID eventDomain, uint32_t *numEvents) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiEventDomainGetNumEvents)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiEventDomainGetNumEvents = (CUptiResult (*)(CUpti_EventDomainID, uint32_t *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiEventDomainGetNumEvents");
			fprintf(stderr, "wrapper_cuptiEventDomainGetNumEvents:%p\n", wrapper_cuptiEventDomainGetNumEvents);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiEventDomainGetNumEvents():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiEventDomainGetNumEvents(eventDomain, numEvents);
		return retval;
	}
}