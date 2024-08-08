#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftEstimate1d)(int, cufftType, int, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftEstimate1d(int nx, cufftType type, int batch, size_t *workSize){
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftEstimate1d)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftEstimate1d = (cufftResult (*)(int, cufftType, int, size_t *)) dlsym(libwrapper_cufft_handle, "wrapper_cufftEstimate1d");
			fprintf(stderr, "wrapper_cufftEstimate1d:%p\n", wrapper_cufftEstimate1d);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftEstimate1d():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftEstimate1d(nx, type, batch, workSize);
		return retval;
	}
}