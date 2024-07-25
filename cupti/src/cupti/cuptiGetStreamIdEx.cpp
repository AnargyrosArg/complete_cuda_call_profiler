#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiGetStreamIdEx)(CUcontext, CUstream, uint8_t, uint32_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiGetStreamIdEx(CUcontext context, CUstream stream, uint8_t perThreadStream, uint32_t *streamId) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiGetStreamIdEx)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiGetStreamIdEx = (CUptiResult (*)(CUcontext, CUstream, uint8_t, uint32_t *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiGetStreamIdEx");
			fprintf(stderr, "wrapper_cuptiGetStreamIdEx:%p\n", wrapper_cuptiGetStreamIdEx);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiGetStreamIdEx():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiGetStreamIdEx(context, stream, perThreadStream, streamId);
		return retval;
	}
}