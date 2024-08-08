#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiSetThreadIdType)(CUpti_ActivityThreadIdType);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiSetThreadIdType(CUpti_ActivityThreadIdType type) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiSetThreadIdType)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiSetThreadIdType = (CUptiResult (*)(CUpti_ActivityThreadIdType)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiSetThreadIdType");
			fprintf(stderr, "wrapper_cuptiSetThreadIdType:%p\n", wrapper_cuptiSetThreadIdType);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiSetThreadIdType():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiSetThreadIdType(type);
		return retval;
	}
}