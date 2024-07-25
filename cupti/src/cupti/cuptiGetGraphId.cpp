#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiGetGraphId)(CUgraph, uint32_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiGetGraphId(CUgraph graph, uint32_t *pId) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiGetGraphId)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiGetGraphId = (CUptiResult (*)(CUgraph, uint32_t *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiGetGraphId");
			fprintf(stderr, "wrapper_cuptiGetGraphId:%p\n", wrapper_cuptiGetGraphId);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiGetGraphId():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiGetGraphId(graph, pId);
		return retval;
	}
}