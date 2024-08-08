#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiGetDeviceId)(CUcontext, uint32_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiGetDeviceId(CUcontext context, uint32_t *deviceId) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiGetDeviceId)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiGetDeviceId = (CUptiResult (*)(CUcontext, uint32_t *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiGetDeviceId");
			fprintf(stderr, "wrapper_cuptiGetDeviceId:%p\n", wrapper_cuptiGetDeviceId);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiGetDeviceId():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiGetDeviceId(context, deviceId);
		return retval;
	}
}