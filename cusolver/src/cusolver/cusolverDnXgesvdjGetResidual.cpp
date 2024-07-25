#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnXgesvdjGetResidual)(cusolverDnHandle_t, gesvdjInfo_t, double *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnXgesvdjGetResidual(cusolverDnHandle_t handle, gesvdjInfo_t info, double *residual) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnXgesvdjGetResidual)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnXgesvdjGetResidual = (cusolverStatus_t (*)(cusolverDnHandle_t, gesvdjInfo_t, double *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnXgesvdjGetResidual");
			fprintf(stderr, "wrapper_cusolverDnXgesvdjGetResidual:%p\n", wrapper_cusolverDnXgesvdjGetResidual);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnXgesvdjGetResidual():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnXgesvdjGetResidual(handle, info, residual);
		return retval;
	}
}