#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiActivityEnableContext)(CUcontext, CUpti_ActivityKind);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiActivityEnableContext(CUcontext context, CUpti_ActivityKind kind) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiActivityEnableContext)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiActivityEnableContext = (CUptiResult (*)(CUcontext, CUpti_ActivityKind)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiActivityEnableContext");
			fprintf(stderr, "wrapper_cuptiActivityEnableContext:%p\n", wrapper_cuptiActivityEnableContext);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiActivityEnableContext():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiActivityEnableContext(context, kind);
		return retval;
	}
}