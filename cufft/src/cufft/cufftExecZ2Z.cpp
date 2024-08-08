#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftExecZ2Z)(cufftHandle, cufftDoubleComplex *, cufftDoubleComplex *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftExecZ2Z(cufftHandle plan, cufftDoubleComplex *idata, cufftDoubleComplex *odata, int direction){
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftExecZ2Z)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftExecZ2Z = (cufftResult (*)(cufftHandle, cufftDoubleComplex *, cufftDoubleComplex *, int)) dlsym(libwrapper_cufft_handle, "wrapper_cufftExecZ2Z");
			fprintf(stderr, "wrapper_cufftExecZ2Z:%p\n", wrapper_cufftExecZ2Z);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftExecZ2Z():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftExecZ2Z(plan, idata, odata, direction);
		return retval;
	}
}