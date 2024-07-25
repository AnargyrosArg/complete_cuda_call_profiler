#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiGetTimestamp)(uint64_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiGetTimestamp(uint64_t *timestamp) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiGetTimestamp)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiGetTimestamp = (CUptiResult (*)(uint64_t *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiGetTimestamp");
			fprintf(stderr, "wrapper_cuptiGetTimestamp:%p\n", wrapper_cuptiGetTimestamp);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiGetTimestamp():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiGetTimestamp(timestamp);
		return retval;
	}
}