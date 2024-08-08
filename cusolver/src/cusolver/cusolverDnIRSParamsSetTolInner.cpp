#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnIRSParamsSetTolInner)(cusolverDnIRSParams_t, double);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnIRSParamsSetTolInner(cusolverDnIRSParams_t params, double val) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnIRSParamsSetTolInner)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnIRSParamsSetTolInner = (cusolverStatus_t (*)(cusolverDnIRSParams_t, double)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnIRSParamsSetTolInner");
			fprintf(stderr, "wrapper_cusolverDnIRSParamsSetTolInner:%p\n", wrapper_cusolverDnIRSParamsSetTolInner);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnIRSParamsSetTolInner():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnIRSParamsSetTolInner(params, val);
		return retval;
	}
}