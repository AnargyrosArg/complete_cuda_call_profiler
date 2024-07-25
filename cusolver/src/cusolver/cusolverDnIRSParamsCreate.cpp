#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnIRSParamsCreate)(cusolverDnIRSParams_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnIRSParamsCreate(cusolverDnIRSParams_t *params_ptr) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnIRSParamsCreate)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnIRSParamsCreate = (cusolverStatus_t (*)(cusolverDnIRSParams_t *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnIRSParamsCreate");
			fprintf(stderr, "wrapper_cusolverDnIRSParamsCreate:%p\n", wrapper_cusolverDnIRSParamsCreate);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnIRSParamsCreate():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnIRSParamsCreate(params_ptr);
		return retval;
	}
}