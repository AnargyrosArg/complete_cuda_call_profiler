#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiSetEventCollectionMode)(CUcontext, CUpti_EventCollectionMode);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiSetEventCollectionMode(CUcontext context, CUpti_EventCollectionMode mode) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiSetEventCollectionMode)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiSetEventCollectionMode = (CUptiResult (*)(CUcontext, CUpti_EventCollectionMode)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiSetEventCollectionMode");
			fprintf(stderr, "wrapper_cuptiSetEventCollectionMode:%p\n", wrapper_cuptiSetEventCollectionMode);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiSetEventCollectionMode():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiSetEventCollectionMode(context, mode);
		return retval;
	}
}