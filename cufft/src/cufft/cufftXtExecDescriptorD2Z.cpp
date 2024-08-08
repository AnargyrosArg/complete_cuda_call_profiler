#include <cufftXt.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftXtExecDescriptorD2Z)(cufftHandle, cudaLibXtDesc *, cudaLibXtDesc *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftXtExecDescriptorD2Z(cufftHandle plan, cudaLibXtDesc *input, cudaLibXtDesc *output){
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftXtExecDescriptorD2Z)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftXtExecDescriptorD2Z = (cufftResult (*)(cufftHandle, cudaLibXtDesc *, cudaLibXtDesc *)) dlsym(libwrapper_cufft_handle, "wrapper_cufftXtExecDescriptorD2Z");
			fprintf(stderr, "wrapper_cufftXtExecDescriptorD2Z:%p\n", wrapper_cufftXtExecDescriptorD2Z);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftXtExecDescriptorD2Z():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftXtExecDescriptorD2Z(plan, input, output);
		return retval;
	}
}