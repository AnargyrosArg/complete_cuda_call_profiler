#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiActivityEnable)(CUpti_ActivityKind);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiActivityEnable(CUpti_ActivityKind kind) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiActivityEnable)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiActivityEnable = (CUptiResult (*)(CUpti_ActivityKind)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiActivityEnable");
			fprintf(stderr, "wrapper_cuptiActivityEnable:%p\n", wrapper_cuptiActivityEnable);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiActivityEnable():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiActivityEnable(kind);
		return retval;
	}
}