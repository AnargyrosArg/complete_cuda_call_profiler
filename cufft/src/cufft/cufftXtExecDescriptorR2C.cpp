#include <cufftXt.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftXtExecDescriptorR2C)(cufftHandle, cudaLibXtDesc *, cudaLibXtDesc *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftXtExecDescriptorR2C(cufftHandle plan, cudaLibXtDesc *input, cudaLibXtDesc *output){
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftXtExecDescriptorR2C)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftXtExecDescriptorR2C = (cufftResult (*)(cufftHandle, cudaLibXtDesc *, cudaLibXtDesc *)) dlsym(libwrapper_cufft_handle, "wrapper_cufftXtExecDescriptorR2C");
			fprintf(stderr, "wrapper_cufftXtExecDescriptorR2C:%p\n", wrapper_cufftXtExecDescriptorR2C);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftXtExecDescriptorR2C():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftXtExecDescriptorR2C(plan, input, output);
		return retval;
	}
}