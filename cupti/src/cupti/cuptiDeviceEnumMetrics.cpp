#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiDeviceEnumMetrics)(CUdevice, size_t *, CUpti_MetricID *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiDeviceEnumMetrics(CUdevice device, size_t *arraySizeBytes, CUpti_MetricID *metricArray) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiDeviceEnumMetrics)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiDeviceEnumMetrics = (CUptiResult (*)(CUdevice, size_t *, CUpti_MetricID *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiDeviceEnumMetrics");
			fprintf(stderr, "wrapper_cuptiDeviceEnumMetrics:%p\n", wrapper_cuptiDeviceEnumMetrics);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiDeviceEnumMetrics():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiDeviceEnumMetrics(device, arraySizeBytes, metricArray);
		return retval;
	}
}