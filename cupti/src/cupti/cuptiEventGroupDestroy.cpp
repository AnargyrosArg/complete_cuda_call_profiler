#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiEventGroupDestroy)(CUpti_EventGroup);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiEventGroupDestroy(CUpti_EventGroup eventGroup) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiEventGroupDestroy)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiEventGroupDestroy = (CUptiResult (*)(CUpti_EventGroup)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiEventGroupDestroy");
			fprintf(stderr, "wrapper_cuptiEventGroupDestroy:%p\n", wrapper_cuptiEventGroupDestroy);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiEventGroupDestroy():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiEventGroupDestroy(eventGroup);
		return retval;
	}
}