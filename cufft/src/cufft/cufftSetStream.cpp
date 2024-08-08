#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftSetStream)(cufftHandle, cudaStream_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftSetStream(cufftHandle plan, cudaStream_t stream){
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftSetStream)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftSetStream = (cufftResult (*)(cufftHandle, cudaStream_t)) dlsym(libwrapper_cufft_handle, "wrapper_cufftSetStream");
			fprintf(stderr, "wrapper_cufftSetStream:%p\n", wrapper_cufftSetStream);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftSetStream():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftSetStream(plan, stream);
		return retval;
	}
}