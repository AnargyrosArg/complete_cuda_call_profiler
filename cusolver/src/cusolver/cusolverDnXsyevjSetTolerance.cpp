#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnXsyevjSetTolerance)(syevjInfo_t, double);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnXsyevjSetTolerance(syevjInfo_t info, double tolerance) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnXsyevjSetTolerance)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnXsyevjSetTolerance = (cusolverStatus_t (*)(syevjInfo_t, double)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnXsyevjSetTolerance");
			fprintf(stderr, "wrapper_cusolverDnXsyevjSetTolerance:%p\n", wrapper_cusolverDnXsyevjSetTolerance);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnXsyevjSetTolerance():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnXsyevjSetTolerance(info, tolerance);
		return retval;
	}
}