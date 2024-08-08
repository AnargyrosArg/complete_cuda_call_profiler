#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftExecC2C)(cufftHandle, cufftComplex *, cufftComplex *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftExecC2C(cufftHandle plan, cufftComplex *idata, cufftComplex *odata, int direction){
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftExecC2C)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftExecC2C = (cufftResult (*)(cufftHandle, cufftComplex *, cufftComplex *, int)) dlsym(libwrapper_cufft_handle, "wrapper_cufftExecC2C");
			fprintf(stderr, "wrapper_cufftExecC2C:%p\n", wrapper_cufftExecC2C);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftExecC2C():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftExecC2C(plan, idata, odata, direction);
		return retval;
	}
}