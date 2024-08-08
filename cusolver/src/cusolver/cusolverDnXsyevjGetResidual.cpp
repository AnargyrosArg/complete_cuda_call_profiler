#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnXsyevjGetResidual)(cusolverDnHandle_t, syevjInfo_t, double *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnXsyevjGetResidual(cusolverDnHandle_t handle, syevjInfo_t info, double *residual) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnXsyevjGetResidual)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnXsyevjGetResidual = (cusolverStatus_t (*)(cusolverDnHandle_t, syevjInfo_t, double *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnXsyevjGetResidual");
			fprintf(stderr, "wrapper_cusolverDnXsyevjGetResidual:%p\n", wrapper_cusolverDnXsyevjGetResidual);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnXsyevjGetResidual():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnXsyevjGetResidual(handle, info, residual);
		return retval;
	}
}