#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiDeviceGetNumMetrics)(CUdevice, uint32_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiDeviceGetNumMetrics(CUdevice device, uint32_t *numMetrics) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiDeviceGetNumMetrics)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiDeviceGetNumMetrics = (CUptiResult (*)(CUdevice, uint32_t *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiDeviceGetNumMetrics");
			fprintf(stderr, "wrapper_cuptiDeviceGetNumMetrics:%p\n", wrapper_cuptiDeviceGetNumMetrics);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiDeviceGetNumMetrics():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiDeviceGetNumMetrics(device, numMetrics);
		return retval;
	}
}