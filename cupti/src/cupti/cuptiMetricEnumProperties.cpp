#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiMetricEnumProperties)(CUpti_MetricID, size_t *, CUpti_MetricPropertyID *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiMetricEnumProperties(CUpti_MetricID metric, size_t *propIdArraySizeBytes, CUpti_MetricPropertyID *propIdArray) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiMetricEnumProperties)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiMetricEnumProperties = (CUptiResult (*)(CUpti_MetricID, size_t *, CUpti_MetricPropertyID *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiMetricEnumProperties");
			fprintf(stderr, "wrapper_cuptiMetricEnumProperties:%p\n", wrapper_cuptiMetricEnumProperties);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiMetricEnumProperties():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiMetricEnumProperties(metric, propIdArraySizeBytes, propIdArray);
		return retval;
	}
}