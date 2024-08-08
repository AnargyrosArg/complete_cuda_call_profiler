#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiComputeCapabilitySupported)(int, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiComputeCapabilitySupported(int major, int minor, int *support) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiComputeCapabilitySupported)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiComputeCapabilitySupported = (CUptiResult (*)(int, int, int *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiComputeCapabilitySupported");
			fprintf(stderr, "wrapper_cuptiComputeCapabilitySupported:%p\n", wrapper_cuptiComputeCapabilitySupported);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiComputeCapabilitySupported():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiComputeCapabilitySupported(major, minor, support);
		return retval;
	}
}