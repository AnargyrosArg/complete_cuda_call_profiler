#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiFinalize)();
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiFinalize() {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiFinalize)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiFinalize = (CUptiResult (*)()) dlsym(libwrapper_cupti_handle, "wrapper_cuptiFinalize");
			fprintf(stderr, "wrapper_cuptiFinalize:%p\n", wrapper_cuptiFinalize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiFinalize():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiFinalize();
		return retval;
	}
}