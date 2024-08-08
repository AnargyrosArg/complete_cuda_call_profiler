#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiEnumMetrics)(size_t *, CUpti_MetricID *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiEnumMetrics(size_t *arraySizeBytes, CUpti_MetricID *metricArray) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiEnumMetrics)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiEnumMetrics = (CUptiResult (*)(size_t *, CUpti_MetricID *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiEnumMetrics");
			fprintf(stderr, "wrapper_cuptiEnumMetrics:%p\n", wrapper_cuptiEnumMetrics);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiEnumMetrics():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiEnumMetrics(arraySizeBytes, metricArray);
		return retval;
	}
}