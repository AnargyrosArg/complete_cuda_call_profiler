#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiGetAutoBoostState)(CUcontext, CUpti_ActivityAutoBoostState *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiGetAutoBoostState(CUcontext context, CUpti_ActivityAutoBoostState *state) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiGetAutoBoostState)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiGetAutoBoostState = (CUptiResult (*)(CUcontext, CUpti_ActivityAutoBoostState *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiGetAutoBoostState");
			fprintf(stderr, "wrapper_cuptiGetAutoBoostState:%p\n", wrapper_cuptiGetAutoBoostState);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiGetAutoBoostState():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiGetAutoBoostState(context, state);
		return retval;
	}
}