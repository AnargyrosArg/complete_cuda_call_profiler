#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiActivityPopExternalCorrelationId)(CUpti_ExternalCorrelationKind, uint64_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiActivityPopExternalCorrelationId(CUpti_ExternalCorrelationKind kind, uint64_t *lastId) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiActivityPopExternalCorrelationId)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiActivityPopExternalCorrelationId = (CUptiResult (*)(CUpti_ExternalCorrelationKind, uint64_t *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiActivityPopExternalCorrelationId");
			fprintf(stderr, "wrapper_cuptiActivityPopExternalCorrelationId:%p\n", wrapper_cuptiActivityPopExternalCorrelationId);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiActivityPopExternalCorrelationId():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiActivityPopExternalCorrelationId(kind, lastId);
		return retval;
	}
}