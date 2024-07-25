#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiGetThreadIdType)(CUpti_ActivityThreadIdType *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiGetThreadIdType(CUpti_ActivityThreadIdType *type) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiGetThreadIdType)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiGetThreadIdType = (CUptiResult (*)(CUpti_ActivityThreadIdType *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiGetThreadIdType");
			fprintf(stderr, "wrapper_cuptiGetThreadIdType:%p\n", wrapper_cuptiGetThreadIdType);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiGetThreadIdType():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiGetThreadIdType(type);
		return retval;
	}
}