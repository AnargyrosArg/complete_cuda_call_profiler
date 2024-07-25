#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiDeviceGetTimestamp)(CUcontext, uint64_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiDeviceGetTimestamp(CUcontext context, uint64_t *timestamp) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiDeviceGetTimestamp)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiDeviceGetTimestamp = (CUptiResult (*)(CUcontext, uint64_t *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiDeviceGetTimestamp");
			fprintf(stderr, "wrapper_cuptiDeviceGetTimestamp:%p\n", wrapper_cuptiDeviceGetTimestamp);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiDeviceGetTimestamp():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiDeviceGetTimestamp(context, timestamp);
		return retval;
	}
}