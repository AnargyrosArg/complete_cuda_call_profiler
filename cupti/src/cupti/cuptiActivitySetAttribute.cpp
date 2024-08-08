#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiActivitySetAttribute)(CUpti_ActivityAttribute, size_t *, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiActivitySetAttribute(CUpti_ActivityAttribute attr, size_t *valueSize, void *value) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiActivitySetAttribute)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiActivitySetAttribute = (CUptiResult (*)(CUpti_ActivityAttribute, size_t *, void *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiActivitySetAttribute");
			fprintf(stderr, "wrapper_cuptiActivitySetAttribute:%p\n", wrapper_cuptiActivitySetAttribute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiActivitySetAttribute():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiActivitySetAttribute(attr, valueSize, value);
		return retval;
	}
}