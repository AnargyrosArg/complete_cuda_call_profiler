#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnIRSParamsDisableFallback)(cusolverDnIRSParams_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnIRSParamsDisableFallback(cusolverDnIRSParams_t params) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnIRSParamsDisableFallback)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnIRSParamsDisableFallback = (cusolverStatus_t (*)(cusolverDnIRSParams_t)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnIRSParamsDisableFallback");
			fprintf(stderr, "wrapper_cusolverDnIRSParamsDisableFallback:%p\n", wrapper_cusolverDnIRSParamsDisableFallback);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnIRSParamsDisableFallback():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnIRSParamsDisableFallback(params);
		return retval;
	}
}