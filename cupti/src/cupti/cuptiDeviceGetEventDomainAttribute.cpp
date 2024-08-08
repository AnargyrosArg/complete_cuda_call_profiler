#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiDeviceGetEventDomainAttribute)(CUdevice, CUpti_EventDomainID, CUpti_EventDomainAttribute, size_t *, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiDeviceGetEventDomainAttribute(CUdevice device, CUpti_EventDomainID eventDomain, CUpti_EventDomainAttribute attrib, size_t *valueSize, void *value) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiDeviceGetEventDomainAttribute)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiDeviceGetEventDomainAttribute = (CUptiResult (*)(CUdevice, CUpti_EventDomainID, CUpti_EventDomainAttribute, size_t *, void *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiDeviceGetEventDomainAttribute");
			fprintf(stderr, "wrapper_cuptiDeviceGetEventDomainAttribute:%p\n", wrapper_cuptiDeviceGetEventDomainAttribute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiDeviceGetEventDomainAttribute():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiDeviceGetEventDomainAttribute(device, eventDomain, attrib, valueSize, value);
		return retval;
	}
}