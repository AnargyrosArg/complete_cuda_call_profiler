#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiEventGroupCreate)(CUcontext, CUpti_EventGroup *, uint32_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiEventGroupCreate(CUcontext context, CUpti_EventGroup *eventGroup, uint32_t flags) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiEventGroupCreate)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiEventGroupCreate = (CUptiResult (*)(CUcontext, CUpti_EventGroup *, uint32_t)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiEventGroupCreate");
			fprintf(stderr, "wrapper_cuptiEventGroupCreate:%p\n", wrapper_cuptiEventGroupCreate);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiEventGroupCreate():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiEventGroupCreate(context, eventGroup, flags);
		return retval;
	}
}