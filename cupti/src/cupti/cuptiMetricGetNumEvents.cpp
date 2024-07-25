#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiMetricGetNumEvents)(CUpti_MetricID, uint32_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiMetricGetNumEvents(CUpti_MetricID metric, uint32_t *numEvents) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiMetricGetNumEvents)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiMetricGetNumEvents = (CUptiResult (*)(CUpti_MetricID, uint32_t *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiMetricGetNumEvents");
			fprintf(stderr, "wrapper_cuptiMetricGetNumEvents:%p\n", wrapper_cuptiMetricGetNumEvents);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiMetricGetNumEvents():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiMetricGetNumEvents(metric, numEvents);
		return retval;
	}
}