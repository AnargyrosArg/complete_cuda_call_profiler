#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiMetricEnumEvents)(CUpti_MetricID, size_t *, CUpti_EventID *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiMetricEnumEvents(CUpti_MetricID metric, size_t *eventIdArraySizeBytes, CUpti_EventID *eventIdArray) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiMetricEnumEvents)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiMetricEnumEvents = (CUptiResult (*)(CUpti_MetricID, size_t *, CUpti_EventID *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiMetricEnumEvents");
			fprintf(stderr, "wrapper_cuptiMetricEnumEvents:%p\n", wrapper_cuptiMetricEnumEvents);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiMetricEnumEvents():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiMetricEnumEvents(metric, eventIdArraySizeBytes, eventIdArray);
		return retval;
	}
}