#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiMetricGetNumProperties)(CUpti_MetricID, uint32_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiMetricGetNumProperties(CUpti_MetricID metric, uint32_t *numProp) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiMetricGetNumProperties)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiMetricGetNumProperties = (CUptiResult (*)(CUpti_MetricID, uint32_t *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiMetricGetNumProperties");
			fprintf(stderr, "wrapper_cuptiMetricGetNumProperties:%p\n", wrapper_cuptiMetricGetNumProperties);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiMetricGetNumProperties():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiMetricGetNumProperties(metric, numProp);
		return retval;
	}
}