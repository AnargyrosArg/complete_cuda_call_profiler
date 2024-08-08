#include <cufftXt.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftXtExecDescriptorZ2Z)(cufftHandle, cudaLibXtDesc *, cudaLibXtDesc *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftXtExecDescriptorZ2Z(cufftHandle plan, cudaLibXtDesc *input, cudaLibXtDesc *output, int direction){
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftXtExecDescriptorZ2Z)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftXtExecDescriptorZ2Z = (cufftResult (*)(cufftHandle, cudaLibXtDesc *, cudaLibXtDesc *, int)) dlsym(libwrapper_cufft_handle, "wrapper_cufftXtExecDescriptorZ2Z");
			fprintf(stderr, "wrapper_cufftXtExecDescriptorZ2Z:%p\n", wrapper_cufftXtExecDescriptorZ2Z);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftXtExecDescriptorZ2Z():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftXtExecDescriptorZ2Z(plan, input, output, direction);
		return retval;
	}
}