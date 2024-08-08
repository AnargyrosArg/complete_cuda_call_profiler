#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiMetricGetAttribute)(CUpti_MetricID, CUpti_MetricAttribute, size_t *, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiMetricGetAttribute(CUpti_MetricID metric, CUpti_MetricAttribute attrib, size_t *valueSize, void *value) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiMetricGetAttribute)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiMetricGetAttribute = (CUptiResult (*)(CUpti_MetricID, CUpti_MetricAttribute, size_t *, void *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiMetricGetAttribute");
			fprintf(stderr, "wrapper_cuptiMetricGetAttribute:%p\n", wrapper_cuptiMetricGetAttribute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiMetricGetAttribute():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiMetricGetAttribute(metric, attrib, valueSize, value);
		return retval;
	}
}