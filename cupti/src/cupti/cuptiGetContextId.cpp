#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiGetContextId)(CUcontext, uint32_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiGetContextId(CUcontext context, uint32_t *contextId) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiGetContextId)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiGetContextId = (CUptiResult (*)(CUcontext, uint32_t *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiGetContextId");
			fprintf(stderr, "wrapper_cuptiGetContextId:%p\n", wrapper_cuptiGetContextId);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiGetContextId():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiGetContextId(context, contextId);
		return retval;
	}
}