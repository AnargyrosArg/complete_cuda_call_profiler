#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiEventGroupSetsDestroy)(CUpti_EventGroupSets *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiEventGroupSetsDestroy(CUpti_EventGroupSets *eventGroupSets) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiEventGroupSetsDestroy)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiEventGroupSetsDestroy = (CUptiResult (*)(CUpti_EventGroupSets *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiEventGroupSetsDestroy");
			fprintf(stderr, "wrapper_cuptiEventGroupSetsDestroy:%p\n", wrapper_cuptiEventGroupSetsDestroy);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiEventGroupSetsDestroy():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiEventGroupSetsDestroy(eventGroupSets);
		return retval;
	}
}