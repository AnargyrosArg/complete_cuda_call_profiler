#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiEventDomainEnumEvents)(CUpti_EventDomainID, size_t *, CUpti_EventID *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiEventDomainEnumEvents(CUpti_EventDomainID eventDomain, size_t *arraySizeBytes, CUpti_EventID *eventArray) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiEventDomainEnumEvents)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiEventDomainEnumEvents = (CUptiResult (*)(CUpti_EventDomainID, size_t *, CUpti_EventID *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiEventDomainEnumEvents");
			fprintf(stderr, "wrapper_cuptiEventDomainEnumEvents:%p\n", wrapper_cuptiEventDomainEnumEvents);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiEventDomainEnumEvents():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiEventDomainEnumEvents(eventDomain, arraySizeBytes, eventArray);
		return retval;
	}
}