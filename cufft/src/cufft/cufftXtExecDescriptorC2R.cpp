#include <cufftXt.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftXtExecDescriptorC2R)(cufftHandle, cudaLibXtDesc *, cudaLibXtDesc *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftXtExecDescriptorC2R(cufftHandle plan, cudaLibXtDesc *input, cudaLibXtDesc *output){
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftXtExecDescriptorC2R)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftXtExecDescriptorC2R = (cufftResult (*)(cufftHandle, cudaLibXtDesc *, cudaLibXtDesc *)) dlsym(libwrapper_cufft_handle, "wrapper_cufftXtExecDescriptorC2R");
			fprintf(stderr, "wrapper_cufftXtExecDescriptorC2R:%p\n", wrapper_cufftXtExecDescriptorC2R);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftXtExecDescriptorC2R():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftXtExecDescriptorC2R(plan, input, output);
		return retval;
	}
}