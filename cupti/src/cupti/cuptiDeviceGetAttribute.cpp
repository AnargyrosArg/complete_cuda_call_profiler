#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiDeviceGetAttribute)(CUdevice, CUpti_DeviceAttribute, size_t *, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiDeviceGetAttribute(CUdevice device, CUpti_DeviceAttribute attrib, size_t *valueSize, void *value) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiDeviceGetAttribute)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiDeviceGetAttribute = (CUptiResult (*)(CUdevice, CUpti_DeviceAttribute, size_t *, void *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiDeviceGetAttribute");
			fprintf(stderr, "wrapper_cuptiDeviceGetAttribute:%p\n", wrapper_cuptiDeviceGetAttribute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiDeviceGetAttribute():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiDeviceGetAttribute(device, attrib, valueSize, value);
		return retval;
	}
}