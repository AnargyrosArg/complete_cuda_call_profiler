#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiActivityDisable)(CUpti_ActivityKind);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiActivityDisable(CUpti_ActivityKind kind) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiActivityDisable)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiActivityDisable = (CUptiResult (*)(CUpti_ActivityKind)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiActivityDisable");
			fprintf(stderr, "wrapper_cuptiActivityDisable:%p\n", wrapper_cuptiActivityDisable);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiActivityDisable():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiActivityDisable(kind);
		return retval;
	}
}