#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiMetricGetIdFromName)(CUdevice, const char *, CUpti_MetricID *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiMetricGetIdFromName(CUdevice device, const char *metricName, CUpti_MetricID *metric) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiMetricGetIdFromName)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiMetricGetIdFromName = (CUptiResult (*)(CUdevice, const char *, CUpti_MetricID *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiMetricGetIdFromName");
			fprintf(stderr, "wrapper_cuptiMetricGetIdFromName:%p\n", wrapper_cuptiMetricGetIdFromName);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiMetricGetIdFromName():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiMetricGetIdFromName(device, metricName, metric);
		return retval;
	}
}