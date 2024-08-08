#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftExecR2C)(cufftHandle, cufftReal *, cufftComplex *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftExecR2C(cufftHandle plan, cufftReal *idata, cufftComplex *odata){
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftExecR2C)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftExecR2C = (cufftResult (*)(cufftHandle, cufftReal *, cufftComplex *)) dlsym(libwrapper_cufft_handle, "wrapper_cufftExecR2C");
			fprintf(stderr, "wrapper_cufftExecR2C:%p\n", wrapper_cufftExecR2C);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftExecR2C():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftExecR2C(plan, idata, odata);
		return retval;
	}
}