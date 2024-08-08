#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiDeviceSupported)(CUdevice, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiDeviceSupported(CUdevice dev, int *support) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiDeviceSupported)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiDeviceSupported = (CUptiResult (*)(CUdevice, int *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiDeviceSupported");
			fprintf(stderr, "wrapper_cuptiDeviceSupported:%p\n", wrapper_cuptiDeviceSupported);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiDeviceSupported():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiDeviceSupported(dev, support);
		return retval;
	}
}