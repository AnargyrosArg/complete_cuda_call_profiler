#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiActivityGetNumDroppedRecords)(CUcontext, uint32_t, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiActivityGetNumDroppedRecords(CUcontext context, uint32_t streamId, size_t *dropped) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiActivityGetNumDroppedRecords)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiActivityGetNumDroppedRecords = (CUptiResult (*)(CUcontext, uint32_t, size_t *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiActivityGetNumDroppedRecords");
			fprintf(stderr, "wrapper_cuptiActivityGetNumDroppedRecords:%p\n", wrapper_cuptiActivityGetNumDroppedRecords);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiActivityGetNumDroppedRecords():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiActivityGetNumDroppedRecords(context, streamId, dropped);
		return retval;
	}
}