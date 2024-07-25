#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiActivityConfigureUnifiedMemoryCounter)(CUpti_ActivityUnifiedMemoryCounterConfig *, uint32_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiActivityConfigureUnifiedMemoryCounter(CUpti_ActivityUnifiedMemoryCounterConfig *config, uint32_t count) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiActivityConfigureUnifiedMemoryCounter)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiActivityConfigureUnifiedMemoryCounter = (CUptiResult (*)(CUpti_ActivityUnifiedMemoryCounterConfig *, uint32_t)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiActivityConfigureUnifiedMemoryCounter");
			fprintf(stderr, "wrapper_cuptiActivityConfigureUnifiedMemoryCounter:%p\n", wrapper_cuptiActivityConfigureUnifiedMemoryCounter);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiActivityConfigureUnifiedMemoryCounter():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiActivityConfigureUnifiedMemoryCounter(config, count);
		return retval;
	}
}