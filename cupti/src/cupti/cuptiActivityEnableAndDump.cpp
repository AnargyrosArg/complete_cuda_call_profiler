#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiActivityEnableAndDump)(CUpti_ActivityKind);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiActivityEnableAndDump(CUpti_ActivityKind kind) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiActivityEnableAndDump)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiActivityEnableAndDump = (CUptiResult (*)(CUpti_ActivityKind)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiActivityEnableAndDump");
			fprintf(stderr, "wrapper_cuptiActivityEnableAndDump:%p\n", wrapper_cuptiActivityEnableAndDump);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiActivityEnableAndDump():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiActivityEnableAndDump(kind);
		return retval;
	}
}