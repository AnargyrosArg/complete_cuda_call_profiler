#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiEnableKernelReplayMode)(CUcontext);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiEnableKernelReplayMode(CUcontext context) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiEnableKernelReplayMode)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiEnableKernelReplayMode = (CUptiResult (*)(CUcontext)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiEnableKernelReplayMode");
			fprintf(stderr, "wrapper_cuptiEnableKernelReplayMode:%p\n", wrapper_cuptiEnableKernelReplayMode);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiEnableKernelReplayMode():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiEnableKernelReplayMode(context);
		return retval;
	}
}