#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiEnumEventDomains)(size_t *, CUpti_EventDomainID *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiEnumEventDomains(size_t *arraySizeBytes, CUpti_EventDomainID *domainArray) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiEnumEventDomains)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiEnumEventDomains = (CUptiResult (*)(size_t *, CUpti_EventDomainID *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiEnumEventDomains");
			fprintf(stderr, "wrapper_cuptiEnumEventDomains:%p\n", wrapper_cuptiEnumEventDomains);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiEnumEventDomains():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiEnumEventDomains(arraySizeBytes, domainArray);
		return retval;
	}
}