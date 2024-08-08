#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiActivityFlushPeriod)(uint32_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiActivityFlushPeriod(uint32_t time) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiActivityFlushPeriod)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiActivityFlushPeriod = (CUptiResult (*)(uint32_t)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiActivityFlushPeriod");
			fprintf(stderr, "wrapper_cuptiActivityFlushPeriod:%p\n", wrapper_cuptiActivityFlushPeriod);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiActivityFlushPeriod():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiActivityFlushPeriod(time);
		return retval;
	}
}