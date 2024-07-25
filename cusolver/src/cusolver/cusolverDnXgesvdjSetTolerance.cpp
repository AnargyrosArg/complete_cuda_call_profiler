#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnXgesvdjSetTolerance)(gesvdjInfo_t, double);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnXgesvdjSetTolerance(gesvdjInfo_t info, double tolerance) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnXgesvdjSetTolerance)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnXgesvdjSetTolerance = (cusolverStatus_t (*)(gesvdjInfo_t, double)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnXgesvdjSetTolerance");
			fprintf(stderr, "wrapper_cusolverDnXgesvdjSetTolerance:%p\n", wrapper_cusolverDnXgesvdjSetTolerance);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnXgesvdjSetTolerance():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnXgesvdjSetTolerance(info, tolerance);
		return retval;
	}
}