#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiGetNumEventDomains)(uint32_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiGetNumEventDomains(uint32_t *numDomains) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiGetNumEventDomains)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiGetNumEventDomains = (CUptiResult (*)(uint32_t *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiGetNumEventDomains");
			fprintf(stderr, "wrapper_cuptiGetNumEventDomains:%p\n", wrapper_cuptiGetNumEventDomains);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiGetNumEventDomains():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiGetNumEventDomains(numDomains);
		return retval;
	}
}