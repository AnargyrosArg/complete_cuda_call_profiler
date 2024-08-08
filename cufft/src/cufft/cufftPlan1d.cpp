#include <cufft.h>
#include <dlfcn.h>
#include <iostream>
cufftResult (*wrapper_cufftPlan1d)(cufftHandle *, int, cufftType, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cufft_handle;
extern "C"
{
	cufftResult cufftPlan1d(cufftHandle *plan, int nx, cufftType type, int batch){
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cufft_handle == NULL){
			libwrapper_cufft_handle = dlopen("libwrapper_cufft.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cufftPlan1d)
		{
			//fetch the original function addr using dlsym
			wrapper_cufftPlan1d = (cufftResult (*)(cufftHandle *, int, cufftType, int)) dlsym(libwrapper_cufft_handle, "wrapper_cufftPlan1d");
			fprintf(stderr, "wrapper_cufftPlan1d:%p\n", wrapper_cufftPlan1d);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cufftPlan1d():%s\n", __dlerror);
			fflush(stderr);
		}
		cufftResult retval = wrapper_cufftPlan1d(plan, nx, type, batch);
		return retval;
	}
}