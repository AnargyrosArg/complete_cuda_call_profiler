#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftSetWorkArea)(cufftHandle, void *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftSetWorkArea(cufftHandle plan, void *workArea){
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftSetWorkArea)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftSetWorkArea = (cufftResult (*)(cufftHandle, void *)) dlsym(libwrapper_cufft_handle, "wrapper_cufftSetWorkArea");
			fprintf(stderr, "wrapper_cufftSetWorkArea:%p\n", wrapper_cufftSetWorkArea);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftSetWorkArea():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftSetWorkArea(plan, workArea);
		return retval;
	}
}