#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnIRSParamsEnableFallback)(cusolverDnIRSParams_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnIRSParamsEnableFallback(cusolverDnIRSParams_t params) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnIRSParamsEnableFallback)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnIRSParamsEnableFallback = (cusolverStatus_t (*)(cusolverDnIRSParams_t)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnIRSParamsEnableFallback");
			fprintf(stderr, "wrapper_cusolverDnIRSParamsEnableFallback:%p\n", wrapper_cusolverDnIRSParamsEnableFallback);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnIRSParamsEnableFallback():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnIRSParamsEnableFallback(params);
		return retval;
	}
}