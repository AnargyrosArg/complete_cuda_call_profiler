#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiMetricCreateEventGroupSets)(CUcontext, size_t, CUpti_MetricID *, CUpti_EventGroupSets **);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiMetricCreateEventGroupSets(CUcontext context, size_t metricIdArraySizeBytes, CUpti_MetricID *metricIdArray, CUpti_EventGroupSets **eventGroupPasses) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiMetricCreateEventGroupSets)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiMetricCreateEventGroupSets = (CUptiResult (*)(CUcontext, size_t, CUpti_MetricID *, CUpti_EventGroupSets **)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiMetricCreateEventGroupSets");
			fprintf(stderr, "wrapper_cuptiMetricCreateEventGroupSets:%p\n", wrapper_cuptiMetricCreateEventGroupSets);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiMetricCreateEventGroupSets():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiMetricCreateEventGroupSets(context, metricIdArraySizeBytes, metricIdArray, eventGroupPasses);
		return retval;
	}
}