#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiGetVersion)(uint32_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiGetVersion(uint32_t *version) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiGetVersion)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiGetVersion = (CUptiResult (*)(uint32_t *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiGetVersion");
			fprintf(stderr, "wrapper_cuptiGetVersion:%p\n", wrapper_cuptiGetVersion);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiGetVersion():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiGetVersion(version);
		return retval;
	}
}