#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiMetricGetValue)(CUdevice, CUpti_MetricID, size_t, CUpti_EventID *, size_t, uint64_t *, uint64_t, CUpti_MetricValue *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiMetricGetValue(CUdevice device, CUpti_MetricID metric, size_t eventIdArraySizeBytes, CUpti_EventID *eventIdArray, size_t eventValueArraySizeBytes, uint64_t *eventValueArray, uint64_t timeDuration, CUpti_MetricValue *metricValue) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiMetricGetValue)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiMetricGetValue = (CUptiResult (*)(CUdevice, CUpti_MetricID, size_t, CUpti_EventID *, size_t, uint64_t *, uint64_t, CUpti_MetricValue *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiMetricGetValue");
			fprintf(stderr, "wrapper_cuptiMetricGetValue:%p\n", wrapper_cuptiMetricGetValue);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiMetricGetValue():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiMetricGetValue(device, metric, eventIdArraySizeBytes, eventIdArray, eventValueArraySizeBytes, eventValueArray, timeDuration, metricValue);
		return retval;
	}
}