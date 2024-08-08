#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnIRSParamsSetSolverLowestPrecision)(cusolverDnIRSParams_t, cusolverPrecType_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnIRSParamsSetSolverLowestPrecision(cusolverDnIRSParams_t params, cusolverPrecType_t solver_lowest_precision) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnIRSParamsSetSolverLowestPrecision)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnIRSParamsSetSolverLowestPrecision = (cusolverStatus_t (*)(cusolverDnIRSParams_t, cusolverPrecType_t)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnIRSParamsSetSolverLowestPrecision");
			fprintf(stderr, "wrapper_cusolverDnIRSParamsSetSolverLowestPrecision:%p\n", wrapper_cusolverDnIRSParamsSetSolverLowestPrecision);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnIRSParamsSetSolverLowestPrecision():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnIRSParamsSetSolverLowestPrecision(params, solver_lowest_precision);
		return retval;
	}
}