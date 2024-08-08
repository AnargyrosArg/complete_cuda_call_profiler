#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiMetricGetValue2)(CUpti_MetricID, size_t, CUpti_EventID *, size_t, uint64_t *, size_t, CUpti_MetricPropertyID *, size_t, uint64_t *, CUpti_MetricValue *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiMetricGetValue2(CUpti_MetricID metric, size_t eventIdArraySizeBytes, CUpti_EventID *eventIdArray, size_t eventValueArraySizeBytes, uint64_t *eventValueArray, size_t propIdArraySizeBytes, CUpti_MetricPropertyID *propIdArray, size_t propValueArraySizeBytes, uint64_t *propValueArray, CUpti_MetricValue *metricValue) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiMetricGetValue2)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiMetricGetValue2 = (CUptiResult (*)(CUpti_MetricID, size_t, CUpti_EventID *, size_t, uint64_t *, size_t, CUpti_MetricPropertyID *, size_t, uint64_t *, CUpti_MetricValue *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiMetricGetValue2");
			fprintf(stderr, "wrapper_cuptiMetricGetValue2:%p\n", wrapper_cuptiMetricGetValue2);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiMetricGetValue2():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiMetricGetValue2(metric, eventIdArraySizeBytes, eventIdArray, eventValueArraySizeBytes, eventValueArray, propIdArraySizeBytes, propIdArray, propValueArraySizeBytes, propValueArray, metricValue);
		return retval;
	}
}