#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiDeviceGetNumEventDomains)(CUdevice, uint32_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiDeviceGetNumEventDomains(CUdevice device, uint32_t *numDomains) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiDeviceGetNumEventDomains)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiDeviceGetNumEventDomains = (CUptiResult (*)(CUdevice, uint32_t *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiDeviceGetNumEventDomains");
			fprintf(stderr, "wrapper_cuptiDeviceGetNumEventDomains:%p\n", wrapper_cuptiDeviceGetNumEventDomains);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiDeviceGetNumEventDomains():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiDeviceGetNumEventDomains(device, numDomains);
		return retval;
	}
}