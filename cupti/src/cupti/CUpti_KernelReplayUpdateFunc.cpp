/*#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
void (*wrapper_CUpti_KernelReplayUpdateFunc)(const char *, int, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	void CUpti_KernelReplayUpdateFunc(const char *kernelName, int numReplaysDone, void *customData) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_CUpti_KernelReplayUpdateFunc)
		{
			//fetch the original function addr using dlsym
			wrapper_CUpti_KernelReplayUpdateFunc = (void (*)(const char *, int, void *)) dlsym(libwrapper_cupti_handle, "wrapper_CUpti_KernelReplayUpdateFunc");
			fprintf(stderr, "wrapper_CUpti_KernelReplayUpdateFunc:%p\n", wrapper_CUpti_KernelReplayUpdateFunc);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function CUpti_KernelReplayUpdateFunc():%s\n", __dlerror);
			fflush(stderr);
		}
		wrapper_CUpti_KernelReplayUpdateFunc(kernelName, numReplaysDone, customData);
	}
}
*/
