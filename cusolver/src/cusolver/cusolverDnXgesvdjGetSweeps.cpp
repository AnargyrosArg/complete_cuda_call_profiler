#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnXgesvdjGetSweeps)(cusolverDnHandle_t, gesvdjInfo_t, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnXgesvdjGetSweeps(cusolverDnHandle_t handle, gesvdjInfo_t info, int *executed_sweeps) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnXgesvdjGetSweeps)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnXgesvdjGetSweeps = (cusolverStatus_t (*)(cusolverDnHandle_t, gesvdjInfo_t, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnXgesvdjGetSweeps");
			fprintf(stderr, "wrapper_cusolverDnXgesvdjGetSweeps:%p\n", wrapper_cusolverDnXgesvdjGetSweeps);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnXgesvdjGetSweeps():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnXgesvdjGetSweeps(handle, info, executed_sweeps);
		return retval;
	}
}