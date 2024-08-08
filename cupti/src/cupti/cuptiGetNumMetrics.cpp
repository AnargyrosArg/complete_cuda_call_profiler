#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiGetNumMetrics)(uint32_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiGetNumMetrics(uint32_t *numMetrics) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiGetNumMetrics)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiGetNumMetrics = (CUptiResult (*)(uint32_t *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiGetNumMetrics");
			fprintf(stderr, "wrapper_cuptiGetNumMetrics:%p\n", wrapper_cuptiGetNumMetrics);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiGetNumMetrics():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiGetNumMetrics(numMetrics);
		return retval;
	}
}