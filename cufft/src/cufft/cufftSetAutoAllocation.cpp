#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftSetAutoAllocation)(cufftHandle, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftSetAutoAllocation(cufftHandle plan, int autoAllocate){
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftSetAutoAllocation)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftSetAutoAllocation = (cufftResult (*)(cufftHandle, int)) dlsym(libwrapper_cufft_handle, "wrapper_cufftSetAutoAllocation");
			fprintf(stderr, "wrapper_cufftSetAutoAllocation:%p\n", wrapper_cufftSetAutoAllocation);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftSetAutoAllocation():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftSetAutoAllocation(plan, autoAllocate);
		return retval;
	}
}