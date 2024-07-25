#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiDisableKernelReplayMode)(CUcontext);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiDisableKernelReplayMode(CUcontext context) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiDisableKernelReplayMode)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiDisableKernelReplayMode = (CUptiResult (*)(CUcontext)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiDisableKernelReplayMode");
			fprintf(stderr, "wrapper_cuptiDisableKernelReplayMode:%p\n", wrapper_cuptiDisableKernelReplayMode);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiDisableKernelReplayMode():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiDisableKernelReplayMode(context);
		return retval;
	}
}