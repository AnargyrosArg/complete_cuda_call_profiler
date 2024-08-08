#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiActivityFlush)(CUcontext, uint32_t, uint32_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiActivityFlush(CUcontext context, uint32_t streamId, uint32_t flag) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiActivityFlush)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiActivityFlush = (CUptiResult (*)(CUcontext, uint32_t, uint32_t)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiActivityFlush");
			fprintf(stderr, "wrapper_cuptiActivityFlush:%p\n", wrapper_cuptiActivityFlush);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiActivityFlush():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiActivityFlush(context, streamId, flag);
		return retval;
	}
}