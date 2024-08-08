#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiEventGroupReadEvent)(CUpti_EventGroup, CUpti_ReadEventFlags, CUpti_EventID, size_t *, uint64_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiEventGroupReadEvent(CUpti_EventGroup eventGroup, CUpti_ReadEventFlags flags, CUpti_EventID event, size_t *eventValueBufferSizeBytes, uint64_t *eventValueBuffer) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiEventGroupReadEvent)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiEventGroupReadEvent = (CUptiResult (*)(CUpti_EventGroup, CUpti_ReadEventFlags, CUpti_EventID, size_t *, uint64_t *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiEventGroupReadEvent");
			fprintf(stderr, "wrapper_cuptiEventGroupReadEvent:%p\n", wrapper_cuptiEventGroupReadEvent);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiEventGroupReadEvent():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiEventGroupReadEvent(eventGroup, flags, event, eventValueBufferSizeBytes, eventValueBuffer);
		return retval;
	}
}