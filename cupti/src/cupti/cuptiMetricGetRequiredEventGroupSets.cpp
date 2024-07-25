#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiMetricGetRequiredEventGroupSets)(CUcontext, CUpti_MetricID, CUpti_EventGroupSets **);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiMetricGetRequiredEventGroupSets(CUcontext context, CUpti_MetricID metric, CUpti_EventGroupSets **eventGroupSets) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiMetricGetRequiredEventGroupSets)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiMetricGetRequiredEventGroupSets = (CUptiResult (*)(CUcontext, CUpti_MetricID, CUpti_EventGroupSets **)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiMetricGetRequiredEventGroupSets");
			fprintf(stderr, "wrapper_cuptiMetricGetRequiredEventGroupSets:%p\n", wrapper_cuptiMetricGetRequiredEventGroupSets);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiMetricGetRequiredEventGroupSets():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiMetricGetRequiredEventGroupSets(context, metric, eventGroupSets);
		return retval;
	}
}