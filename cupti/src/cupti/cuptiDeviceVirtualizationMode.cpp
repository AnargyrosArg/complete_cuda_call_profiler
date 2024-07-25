#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiDeviceVirtualizationMode)(CUdevice, CUpti_DeviceVirtualizationMode *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiDeviceVirtualizationMode(CUdevice dev, CUpti_DeviceVirtualizationMode *mode) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiDeviceVirtualizationMode)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiDeviceVirtualizationMode = (CUptiResult (*)(CUdevice, CUpti_DeviceVirtualizationMode *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiDeviceVirtualizationMode");
			fprintf(stderr, "wrapper_cuptiDeviceVirtualizationMode:%p\n", wrapper_cuptiDeviceVirtualizationMode);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiDeviceVirtualizationMode():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiDeviceVirtualizationMode(dev, mode);
		return retval;
	}
}