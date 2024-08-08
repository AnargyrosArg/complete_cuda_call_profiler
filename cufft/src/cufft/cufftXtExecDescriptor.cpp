#include <cufftXt.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftXtExecDescriptor)(cufftHandle, cudaLibXtDesc *, cudaLibXtDesc *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftXtExecDescriptor(cufftHandle plan, cudaLibXtDesc *input, cudaLibXtDesc *output, int direction){
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftXtExecDescriptor)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftXtExecDescriptor = (cufftResult (*)(cufftHandle, cudaLibXtDesc *, cudaLibXtDesc *, int)) dlsym(libwrapper_cufft_handle, "wrapper_cufftXtExecDescriptor");
			fprintf(stderr, "wrapper_cufftXtExecDescriptor:%p\n", wrapper_cufftXtExecDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftXtExecDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftXtExecDescriptor(plan, input, output, direction);
		return retval;
	}
}