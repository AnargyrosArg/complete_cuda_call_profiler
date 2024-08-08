#include <cufftXt.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftXtSetWorkArea)(cufftHandle, void **);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftXtSetWorkArea(cufftHandle plan, void **workArea){
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftXtSetWorkArea)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftXtSetWorkArea = (cufftResult (*)(cufftHandle, void **)) dlsym(libwrapper_cufft_handle, "wrapper_cufftXtSetWorkArea");
			fprintf(stderr, "wrapper_cufftXtSetWorkArea:%p\n", wrapper_cufftXtSetWorkArea);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftXtSetWorkArea():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftXtSetWorkArea(plan, workArea);
		return retval;
	}
}