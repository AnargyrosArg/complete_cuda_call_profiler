#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiActivityEnableLatencyTimestamps)(uint8_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiActivityEnableLatencyTimestamps(uint8_t enable) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiActivityEnableLatencyTimestamps)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiActivityEnableLatencyTimestamps = (CUptiResult (*)(uint8_t)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiActivityEnableLatencyTimestamps");
			fprintf(stderr, "wrapper_cuptiActivityEnableLatencyTimestamps:%p\n", wrapper_cuptiActivityEnableLatencyTimestamps);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiActivityEnableLatencyTimestamps():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiActivityEnableLatencyTimestamps(enable);
		return retval;
	}
}