#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiGetResultString)(CUptiResult, const char **);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiGetResultString(CUptiResult result, const char **str) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiGetResultString)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiGetResultString = (CUptiResult (*)(CUptiResult, const char **)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiGetResultString");
			fprintf(stderr, "wrapper_cuptiGetResultString:%p\n", wrapper_cuptiGetResultString);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiGetResultString():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiGetResultString(result, str);
		return retval;
	}
}