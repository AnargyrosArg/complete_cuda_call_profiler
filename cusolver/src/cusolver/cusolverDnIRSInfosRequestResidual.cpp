#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnIRSInfosRequestResidual)(cusolverDnIRSInfos_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnIRSInfosRequestResidual(cusolverDnIRSInfos_t infos) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnIRSInfosRequestResidual)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnIRSInfosRequestResidual = (cusolverStatus_t (*)(cusolverDnIRSInfos_t)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnIRSInfosRequestResidual");
			fprintf(stderr, "wrapper_cusolverDnIRSInfosRequestResidual:%p\n", wrapper_cusolverDnIRSInfosRequestResidual);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnIRSInfosRequestResidual():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnIRSInfosRequestResidual(infos);
		return retval;
	}
}