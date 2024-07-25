#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiEventGroupDisable)(CUpti_EventGroup);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiEventGroupDisable(CUpti_EventGroup eventGroup) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiEventGroupDisable)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiEventGroupDisable = (CUptiResult (*)(CUpti_EventGroup)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiEventGroupDisable");
			fprintf(stderr, "wrapper_cuptiEventGroupDisable:%p\n", wrapper_cuptiEventGroupDisable);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiEventGroupDisable():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiEventGroupDisable(eventGroup);
		return retval;
	}
}