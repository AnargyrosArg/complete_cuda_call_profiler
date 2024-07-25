#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiEventGroupSetDisable)(CUpti_EventGroupSet *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiEventGroupSetDisable(CUpti_EventGroupSet *eventGroupSet) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiEventGroupSetDisable)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiEventGroupSetDisable = (CUptiResult (*)(CUpti_EventGroupSet *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiEventGroupSetDisable");
			fprintf(stderr, "wrapper_cuptiEventGroupSetDisable:%p\n", wrapper_cuptiEventGroupSetDisable);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiEventGroupSetDisable():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiEventGroupSetDisable(eventGroupSet);
		return retval;
	}
}