#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnIRSParamsDestroy)(cusolverDnIRSParams_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnIRSParamsDestroy(cusolverDnIRSParams_t params) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnIRSParamsDestroy)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnIRSParamsDestroy = (cusolverStatus_t (*)(cusolverDnIRSParams_t)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnIRSParamsDestroy");
			fprintf(stderr, "wrapper_cusolverDnIRSParamsDestroy:%p\n", wrapper_cusolverDnIRSParamsDestroy);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnIRSParamsDestroy():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnIRSParamsDestroy(params);
		return retval;
	}
}