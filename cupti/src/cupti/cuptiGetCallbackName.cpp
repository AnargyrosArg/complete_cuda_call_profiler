#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiGetCallbackName)(CUpti_CallbackDomain, uint32_t, const char **);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiGetCallbackName(CUpti_CallbackDomain domain, uint32_t cbid, const char **name) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiGetCallbackName)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiGetCallbackName = (CUptiResult (*)(CUpti_CallbackDomain, uint32_t, const char **)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiGetCallbackName");
			fprintf(stderr, "wrapper_cuptiGetCallbackName:%p\n", wrapper_cuptiGetCallbackName);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiGetCallbackName():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiGetCallbackName(domain, cbid, name);
		return retval;
	}
}