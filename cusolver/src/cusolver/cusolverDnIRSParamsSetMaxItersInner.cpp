#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnIRSParamsSetMaxItersInner)(cusolverDnIRSParams_t, cusolver_int_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnIRSParamsSetMaxItersInner(cusolverDnIRSParams_t params, cusolver_int_t maxiters_inner) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnIRSParamsSetMaxItersInner)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnIRSParamsSetMaxItersInner = (cusolverStatus_t (*)(cusolverDnIRSParams_t, cusolver_int_t)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnIRSParamsSetMaxItersInner");
			fprintf(stderr, "wrapper_cusolverDnIRSParamsSetMaxItersInner:%p\n", wrapper_cusolverDnIRSParamsSetMaxItersInner);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnIRSParamsSetMaxItersInner():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnIRSParamsSetMaxItersInner(params, maxiters_inner);
		return retval;
	}
}