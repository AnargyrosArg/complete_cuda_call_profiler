#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiKernelReplaySubscribeUpdate)(CUpti_KernelReplayUpdateFunc, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiKernelReplaySubscribeUpdate(CUpti_KernelReplayUpdateFunc updateFunc, void *customData) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiKernelReplaySubscribeUpdate)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiKernelReplaySubscribeUpdate = (CUptiResult (*)(CUpti_KernelReplayUpdateFunc, void *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiKernelReplaySubscribeUpdate");
			fprintf(stderr, "wrapper_cuptiKernelReplaySubscribeUpdate:%p\n", wrapper_cuptiKernelReplaySubscribeUpdate);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiKernelReplaySubscribeUpdate():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiKernelReplaySubscribeUpdate(updateFunc, customData);
		return retval;
	}
}