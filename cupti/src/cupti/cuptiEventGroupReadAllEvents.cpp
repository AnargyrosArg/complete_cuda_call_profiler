#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiEventGroupReadAllEvents)(CUpti_EventGroup, CUpti_ReadEventFlags, size_t *, uint64_t *, size_t *, CUpti_EventID *, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiEventGroupReadAllEvents(CUpti_EventGroup eventGroup, CUpti_ReadEventFlags flags, size_t *eventValueBufferSizeBytes, uint64_t *eventValueBuffer, size_t *eventIdArraySizeBytes, CUpti_EventID *eventIdArray, size_t *numEventIdsRead) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiEventGroupReadAllEvents)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiEventGroupReadAllEvents = (CUptiResult (*)(CUpti_EventGroup, CUpti_ReadEventFlags, size_t *, uint64_t *, size_t *, CUpti_EventID *, size_t *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiEventGroupReadAllEvents");
			fprintf(stderr, "wrapper_cuptiEventGroupReadAllEvents:%p\n", wrapper_cuptiEventGroupReadAllEvents);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiEventGroupReadAllEvents():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiEventGroupReadAllEvents(eventGroup, flags, eventValueBufferSizeBytes, eventValueBuffer, eventIdArraySizeBytes, eventIdArray, numEventIdsRead);
		return retval;
	}
}