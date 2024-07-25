#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnIRSParamsGetMaxIters)(cusolverDnIRSParams_t, cusolver_int_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnIRSParamsGetMaxIters(cusolverDnIRSParams_t params, cusolver_int_t *maxiters) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnIRSParamsGetMaxIters)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnIRSParamsGetMaxIters = (cusolverStatus_t (*)(cusolverDnIRSParams_t, cusolver_int_t *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnIRSParamsGetMaxIters");
			fprintf(stderr, "wrapper_cusolverDnIRSParamsGetMaxIters:%p\n", wrapper_cusolverDnIRSParamsGetMaxIters);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnIRSParamsGetMaxIters():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnIRSParamsGetMaxIters(params, maxiters);
		return retval;
	}
}