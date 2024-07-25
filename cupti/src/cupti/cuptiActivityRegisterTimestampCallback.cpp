#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiActivityRegisterTimestampCallback)(CUpti_TimestampCallbackFunc);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiActivityRegisterTimestampCallback(CUpti_TimestampCallbackFunc funcTimestamp) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiActivityRegisterTimestampCallback)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiActivityRegisterTimestampCallback = (CUptiResult (*)(CUpti_TimestampCallbackFunc)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiActivityRegisterTimestampCallback");
			fprintf(stderr, "wrapper_cuptiActivityRegisterTimestampCallback:%p\n", wrapper_cuptiActivityRegisterTimestampCallback);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiActivityRegisterTimestampCallback():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiActivityRegisterTimestampCallback(funcTimestamp);
		return retval;
	}
}