#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftExecD2Z)(cufftHandle, cufftDoubleReal *, cufftDoubleComplex *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftExecD2Z(cufftHandle plan, cufftDoubleReal *idata, cufftDoubleComplex *odata){
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftExecD2Z)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftExecD2Z = (cufftResult (*)(cufftHandle, cufftDoubleReal *, cufftDoubleComplex *)) dlsym(libwrapper_cufft_handle, "wrapper_cufftExecD2Z");
			fprintf(stderr, "wrapper_cufftExecD2Z:%p\n", wrapper_cufftExecD2Z);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftExecD2Z():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftExecD2Z(plan, idata, odata);
		return retval;
	}
}