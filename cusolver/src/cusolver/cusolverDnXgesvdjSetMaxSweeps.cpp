#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnXgesvdjSetMaxSweeps)(gesvdjInfo_t, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnXgesvdjSetMaxSweeps(gesvdjInfo_t info, int max_sweeps) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnXgesvdjSetMaxSweeps)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnXgesvdjSetMaxSweeps = (cusolverStatus_t (*)(gesvdjInfo_t, int)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnXgesvdjSetMaxSweeps");
			fprintf(stderr, "wrapper_cusolverDnXgesvdjSetMaxSweeps:%p\n", wrapper_cusolverDnXgesvdjSetMaxSweeps);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnXgesvdjSetMaxSweeps():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnXgesvdjSetMaxSweeps(info, max_sweeps);
		return retval;
	}
}