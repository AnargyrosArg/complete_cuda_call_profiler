#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnIRSParamsSetTol)(cusolverDnIRSParams_t, double);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnIRSParamsSetTol(cusolverDnIRSParams_t params, double val) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnIRSParamsSetTol)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnIRSParamsSetTol = (cusolverStatus_t (*)(cusolverDnIRSParams_t, double)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnIRSParamsSetTol");
			fprintf(stderr, "wrapper_cusolverDnIRSParamsSetTol:%p\n", wrapper_cusolverDnIRSParamsSetTol);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnIRSParamsSetTol():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnIRSParamsSetTol(params, val);
		return retval;
	}
}