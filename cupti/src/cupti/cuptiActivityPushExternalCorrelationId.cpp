#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiActivityPushExternalCorrelationId)(CUpti_ExternalCorrelationKind, uint64_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiActivityPushExternalCorrelationId(CUpti_ExternalCorrelationKind kind, uint64_t id) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiActivityPushExternalCorrelationId)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiActivityPushExternalCorrelationId = (CUptiResult (*)(CUpti_ExternalCorrelationKind, uint64_t)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiActivityPushExternalCorrelationId");
			fprintf(stderr, "wrapper_cuptiActivityPushExternalCorrelationId:%p\n", wrapper_cuptiActivityPushExternalCorrelationId);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiActivityPushExternalCorrelationId():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiActivityPushExternalCorrelationId(kind, id);
		return retval;
	}
}