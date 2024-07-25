#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiEventGroupGetAttribute)(CUpti_EventGroup, CUpti_EventGroupAttribute, size_t *, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiEventGroupGetAttribute(CUpti_EventGroup eventGroup, CUpti_EventGroupAttribute attrib, size_t *valueSize, void *value) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiEventGroupGetAttribute)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiEventGroupGetAttribute = (CUptiResult (*)(CUpti_EventGroup, CUpti_EventGroupAttribute, size_t *, void *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiEventGroupGetAttribute");
			fprintf(stderr, "wrapper_cuptiEventGroupGetAttribute:%p\n", wrapper_cuptiEventGroupGetAttribute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiEventGroupGetAttribute():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiEventGroupGetAttribute(eventGroup, attrib, valueSize, value);
		return retval;
	}
}