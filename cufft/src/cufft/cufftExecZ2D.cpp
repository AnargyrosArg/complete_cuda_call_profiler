#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftExecZ2D)(cufftHandle, cufftDoubleComplex *, cufftDoubleReal *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftExecZ2D(cufftHandle plan, cufftDoubleComplex *idata, cufftDoubleReal *odata) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftExecZ2D)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftExecZ2D = (cufftResult (*)(cufftHandle, cufftDoubleComplex *, cufftDoubleReal *)) dlsym(libwrapper_cufft_handle, "wrapper_cufftExecZ2D");
			fprintf(stderr, "wrapper_cufftExecZ2D:%p\n", wrapper_cufftExecZ2D);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftExecZ2D():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftExecZ2D(plan, idata, odata);
		return retval;
	}
}