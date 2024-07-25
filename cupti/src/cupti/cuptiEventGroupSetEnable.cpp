#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiEventGroupSetEnable)(CUpti_EventGroupSet *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiEventGroupSetEnable(CUpti_EventGroupSet *eventGroupSet) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiEventGroupSetEnable)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiEventGroupSetEnable = (CUptiResult (*)(CUpti_EventGroupSet *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiEventGroupSetEnable");
			fprintf(stderr, "wrapper_cuptiEventGroupSetEnable:%p\n", wrapper_cuptiEventGroupSetEnable);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiEventGroupSetEnable():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiEventGroupSetEnable(eventGroupSet);
		return retval;
	}
}