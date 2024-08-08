#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiGetGraphNodeId)(CUgraphNode, uint64_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiGetGraphNodeId(CUgraphNode node, uint64_t *nodeId) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiGetGraphNodeId)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiGetGraphNodeId = (CUptiResult (*)(CUgraphNode, uint64_t *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiGetGraphNodeId");
			fprintf(stderr, "wrapper_cuptiGetGraphNodeId:%p\n", wrapper_cuptiGetGraphNodeId);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiGetGraphNodeId():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiGetGraphNodeId(node, nodeId);
		return retval;
	}
}