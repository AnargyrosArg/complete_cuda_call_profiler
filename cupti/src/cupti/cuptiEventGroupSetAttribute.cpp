#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiEventGroupSetAttribute)(CUpti_EventGroup, CUpti_EventGroupAttribute, size_t, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiEventGroupSetAttribute(CUpti_EventGroup eventGroup, CUpti_EventGroupAttribute attrib, size_t valueSize, void *value) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiEventGroupSetAttribute)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiEventGroupSetAttribute = (CUptiResult (*)(CUpti_EventGroup, CUpti_EventGroupAttribute, size_t, void *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiEventGroupSetAttribute");
			fprintf(stderr, "wrapper_cuptiEventGroupSetAttribute:%p\n", wrapper_cuptiEventGroupSetAttribute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiEventGroupSetAttribute():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiEventGroupSetAttribute(eventGroup, attrib, valueSize, value);
		return retval;
	}
}