#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnIRSInfosGetResidualHistory)(cusolverDnIRSInfos_t, void **);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnIRSInfosGetResidualHistory(cusolverDnIRSInfos_t infos, void **residual_history) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnIRSInfosGetResidualHistory)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnIRSInfosGetResidualHistory = (cusolverStatus_t (*)(cusolverDnIRSInfos_t, void **)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnIRSInfosGetResidualHistory");
			fprintf(stderr, "wrapper_cusolverDnIRSInfosGetResidualHistory:%p\n", wrapper_cusolverDnIRSInfosGetResidualHistory);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnIRSInfosGetResidualHistory():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnIRSInfosGetResidualHistory(infos, residual_history);
		return retval;
	}
}