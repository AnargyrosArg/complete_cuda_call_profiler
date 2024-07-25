#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnXsyevjSetMaxSweeps)(syevjInfo_t, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnXsyevjSetMaxSweeps(syevjInfo_t info, int max_sweeps) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnXsyevjSetMaxSweeps)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnXsyevjSetMaxSweeps = (cusolverStatus_t (*)(syevjInfo_t, int)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnXsyevjSetMaxSweeps");
			fprintf(stderr, "wrapper_cusolverDnXsyevjSetMaxSweeps:%p\n", wrapper_cusolverDnXsyevjSetMaxSweeps);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnXsyevjSetMaxSweeps():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnXsyevjSetMaxSweeps(info, max_sweeps);
		return retval;
	}
}