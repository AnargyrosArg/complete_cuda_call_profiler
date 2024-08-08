#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiEventDomainGetAttribute)(CUpti_EventDomainID, CUpti_EventDomainAttribute, size_t *, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiEventDomainGetAttribute(CUpti_EventDomainID eventDomain, CUpti_EventDomainAttribute attrib, size_t *valueSize, void *value) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiEventDomainGetAttribute)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiEventDomainGetAttribute = (CUptiResult (*)(CUpti_EventDomainID, CUpti_EventDomainAttribute, size_t *, void *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiEventDomainGetAttribute");
			fprintf(stderr, "wrapper_cuptiEventDomainGetAttribute:%p\n", wrapper_cuptiEventDomainGetAttribute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiEventDomainGetAttribute():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiEventDomainGetAttribute(eventDomain, attrib, valueSize, value);
		return retval;
	}
}