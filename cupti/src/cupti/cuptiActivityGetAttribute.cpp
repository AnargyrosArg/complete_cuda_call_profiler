#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiActivityGetAttribute)(CUpti_ActivityAttribute, size_t *, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiActivityGetAttribute(CUpti_ActivityAttribute attr, size_t *valueSize, void *value) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiActivityGetAttribute)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiActivityGetAttribute = (CUptiResult (*)(CUpti_ActivityAttribute, size_t *, void *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiActivityGetAttribute");
			fprintf(stderr, "wrapper_cuptiActivityGetAttribute:%p\n", wrapper_cuptiActivityGetAttribute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiActivityGetAttribute():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiActivityGetAttribute(attr, valueSize, value);
		return retval;
	}
}