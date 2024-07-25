#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiEventGetIdFromName)(CUdevice, const char *, CUpti_EventID *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiEventGetIdFromName(CUdevice device, const char *eventName, CUpti_EventID *event) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiEventGetIdFromName)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiEventGetIdFromName = (CUptiResult (*)(CUdevice, const char *, CUpti_EventID *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiEventGetIdFromName");
			fprintf(stderr, "wrapper_cuptiEventGetIdFromName:%p\n", wrapper_cuptiEventGetIdFromName);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiEventGetIdFromName():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiEventGetIdFromName(device, eventName, event);
		return retval;
	}
}