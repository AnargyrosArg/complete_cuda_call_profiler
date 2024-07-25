#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiEventGetAttribute)(CUpti_EventID, CUpti_EventAttribute, size_t *, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiEventGetAttribute(CUpti_EventID event, CUpti_EventAttribute attrib, size_t *valueSize, void *value) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiEventGetAttribute)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiEventGetAttribute = (CUptiResult (*)(CUpti_EventID, CUpti_EventAttribute, size_t *, void *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiEventGetAttribute");
			fprintf(stderr, "wrapper_cuptiEventGetAttribute:%p\n", wrapper_cuptiEventGetAttribute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiEventGetAttribute():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiEventGetAttribute(event, attrib, valueSize, value);
		return retval;
	}
}