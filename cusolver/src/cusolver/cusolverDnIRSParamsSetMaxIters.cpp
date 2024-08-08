#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnIRSParamsSetMaxIters)(cusolverDnIRSParams_t, cusolver_int_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnIRSParamsSetMaxIters(cusolverDnIRSParams_t params, cusolver_int_t maxiters) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnIRSParamsSetMaxIters)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnIRSParamsSetMaxIters = (cusolverStatus_t (*)(cusolverDnIRSParams_t, cusolver_int_t)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnIRSParamsSetMaxIters");
			fprintf(stderr, "wrapper_cusolverDnIRSParamsSetMaxIters:%p\n", wrapper_cusolverDnIRSParamsSetMaxIters);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnIRSParamsSetMaxIters():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnIRSParamsSetMaxIters(params, maxiters);
		return retval;
	}
}