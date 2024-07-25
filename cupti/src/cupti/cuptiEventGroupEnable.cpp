#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiEventGroupEnable)(CUpti_EventGroup);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiEventGroupEnable(CUpti_EventGroup eventGroup) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiEventGroupEnable)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiEventGroupEnable = (CUptiResult (*)(CUpti_EventGroup)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiEventGroupEnable");
			fprintf(stderr, "wrapper_cuptiEventGroupEnable:%p\n", wrapper_cuptiEventGroupEnable);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiEventGroupEnable():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiEventGroupEnable(eventGroup);
		return retval;
	}
}