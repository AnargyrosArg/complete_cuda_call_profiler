#include <cufftXt.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftXtSetWorkAreaPolicy)(cufftHandle, cufftXtWorkAreaPolicy, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftXtSetWorkAreaPolicy(cufftHandle plan, cufftXtWorkAreaPolicy policy, size_t *workSize){
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftXtSetWorkAreaPolicy)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftXtSetWorkAreaPolicy = (cufftResult (*)(cufftHandle, cufftXtWorkAreaPolicy, size_t *)) dlsym(libwrapper_cufft_handle, "wrapper_cufftXtSetWorkAreaPolicy");
			fprintf(stderr, "wrapper_cufftXtSetWorkAreaPolicy:%p\n", wrapper_cufftXtSetWorkAreaPolicy);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftXtSetWorkAreaPolicy():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftXtSetWorkAreaPolicy(plan, policy, workSize);
		return retval;
	}
}