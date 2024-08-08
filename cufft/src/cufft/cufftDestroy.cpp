#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftDestroy)(cufftHandle);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftDestroy(cufftHandle plan){
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftDestroy)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftDestroy = (cufftResult (*)(cufftHandle)) dlsym(libwrapper_cufft_handle, "wrapper_cufftDestroy");
			fprintf(stderr, "wrapper_cufftDestroy:%p\n", wrapper_cufftDestroy);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftDestroy():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftDestroy(plan);
		return retval;
	}
}