#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiGetStreamId)(CUcontext, CUstream, uint32_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiGetStreamId(CUcontext context, CUstream stream, uint32_t *streamId) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiGetStreamId)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiGetStreamId = (CUptiResult (*)(CUcontext, CUstream, uint32_t *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiGetStreamId");
			fprintf(stderr, "wrapper_cuptiGetStreamId:%p\n", wrapper_cuptiGetStreamId);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiGetStreamId():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiGetStreamId(context, stream, streamId);
		return retval;
	}
}