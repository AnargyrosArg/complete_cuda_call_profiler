#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnXsyevjGetSweeps)(cusolverDnHandle_t, syevjInfo_t, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnXsyevjGetSweeps(cusolverDnHandle_t handle, syevjInfo_t info, int *executed_sweeps) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnXsyevjGetSweeps)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnXsyevjGetSweeps = (cusolverStatus_t (*)(cusolverDnHandle_t, syevjInfo_t, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnXsyevjGetSweeps");
			fprintf(stderr, "wrapper_cusolverDnXsyevjGetSweeps:%p\n", wrapper_cusolverDnXsyevjGetSweeps);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnXsyevjGetSweeps():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnXsyevjGetSweeps(handle, info, executed_sweeps);
		return retval;
	}
}