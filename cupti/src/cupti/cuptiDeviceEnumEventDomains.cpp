#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiDeviceEnumEventDomains)(CUdevice, size_t *, CUpti_EventDomainID *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiDeviceEnumEventDomains(CUdevice device, size_t *arraySizeBytes, CUpti_EventDomainID *domainArray) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiDeviceEnumEventDomains)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiDeviceEnumEventDomains = (CUptiResult (*)(CUdevice, size_t *, CUpti_EventDomainID *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiDeviceEnumEventDomains");
			fprintf(stderr, "wrapper_cuptiDeviceEnumEventDomains:%p\n", wrapper_cuptiDeviceEnumEventDomains);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiDeviceEnumEventDomains():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiDeviceEnumEventDomains(device, arraySizeBytes, domainArray);
		return retval;
	}
}