#include <cupti.h>
#include <dlfcn.h>
#include <iostream>
CUptiResult (*wrapper_cuptiActivityConfigurePCSampling)(CUcontext, CUpti_ActivityPCSamplingConfig *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cupti_handle;
extern "C"
{
	CUptiResult cuptiActivityConfigurePCSampling(CUcontext ctx, CUpti_ActivityPCSamplingConfig *config) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cupti_handle == NULL){
			libwrapper_cupti_handle = dlopen("libwrapper_cupti.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cuptiActivityConfigurePCSampling)
		{
			//fetch the original function addr using dlsym
			wrapper_cuptiActivityConfigurePCSampling = (CUptiResult (*)(CUcontext, CUpti_ActivityPCSamplingConfig *)) dlsym(libwrapper_cupti_handle, "wrapper_cuptiActivityConfigurePCSampling");
			fprintf(stderr, "wrapper_cuptiActivityConfigurePCSampling:%p\n", wrapper_cuptiActivityConfigurePCSampling);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cuptiActivityConfigurePCSampling():%s\n", __dlerror);
			fflush(stderr);
		}
		CUptiResult retval = wrapper_cuptiActivityConfigurePCSampling(ctx, config);
		return retval;
	}
}