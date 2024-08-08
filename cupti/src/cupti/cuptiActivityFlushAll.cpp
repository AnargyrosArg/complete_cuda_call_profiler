#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiActivityFlushAll)(uint32_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiActivityFlushAll(uint32_t flag) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiActivityFlushAll)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiActivityFlushAll = (CUptiResult (*)(uint32_t)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiActivityFlushAll");
			fprintf(stderr, "wrapper_cuptiActivityFlushAll:%p\n", wrapper_cuptiActivityFlushAll);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiActivityFlushAll():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiActivityFlushAll(flag);
		return retval;
	}
}