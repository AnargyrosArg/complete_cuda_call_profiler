#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftExecC2R)(cufftHandle, cufftComplex *, cufftReal *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftExecC2R(cufftHandle plan, cufftComplex *idata, cufftReal *odata) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftExecC2R)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftExecC2R = (cufftResult (*)(cufftHandle, cufftComplex *, cufftReal *)) dlsym(libwrapper_cufft_handle, "wrapper_cufftExecC2R");
			fprintf(stderr, "wrapper_cufftExecC2R:%p\n", wrapper_cufftExecC2R);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftExecC2R():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftExecC2R(plan, idata, odata);
		return retval;
	}
}