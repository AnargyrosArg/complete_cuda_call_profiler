#include <cufftXt.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftXtExecDescriptorC2C)(cufftHandle, cudaLibXtDesc *, cudaLibXtDesc *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftXtExecDescriptorC2C(cufftHandle plan, cudaLibXtDesc *input, cudaLibXtDesc *output, int direction){
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftXtExecDescriptorC2C)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftXtExecDescriptorC2C = (cufftResult (*)(cufftHandle, cudaLibXtDesc *, cudaLibXtDesc *, int)) dlsym(libwrapper_cufft_handle, "wrapper_cufftXtExecDescriptorC2C");
			fprintf(stderr, "wrapper_cufftXtExecDescriptorC2C:%p\n", wrapper_cufftXtExecDescriptorC2C);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftXtExecDescriptorC2C():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftXtExecDescriptorC2C(plan, input, output, direction);
		return retval;
	}
}