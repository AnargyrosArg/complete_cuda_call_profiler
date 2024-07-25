#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiEventGroupSetsCreate)(CUcontext, size_t, CUpti_EventID *, CUpti_EventGroupSets **);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiEventGroupSetsCreate(CUcontext context, size_t eventIdArraySizeBytes, CUpti_EventID *eventIdArray, CUpti_EventGroupSets **eventGroupPasses) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiEventGroupSetsCreate)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiEventGroupSetsCreate = (CUptiResult (*)(CUcontext, size_t, CUpti_EventID *, CUpti_EventGroupSets **)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiEventGroupSetsCreate");
			fprintf(stderr, "wrapper_cuptiEventGroupSetsCreate:%p\n", wrapper_cuptiEventGroupSetsCreate);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiEventGroupSetsCreate():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiEventGroupSetsCreate(context, eventIdArraySizeBytes, eventIdArray, eventGroupPasses);
		return retval;
	}
}