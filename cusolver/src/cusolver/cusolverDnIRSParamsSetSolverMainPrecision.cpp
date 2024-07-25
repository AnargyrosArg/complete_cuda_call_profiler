#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnIRSParamsSetSolverMainPrecision)(cusolverDnIRSParams_t, cusolverPrecType_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnIRSParamsSetSolverMainPrecision(cusolverDnIRSParams_t params, cusolverPrecType_t solver_main_precision) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnIRSParamsSetSolverMainPrecision)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnIRSParamsSetSolverMainPrecision = (cusolverStatus_t (*)(cusolverDnIRSParams_t, cusolverPrecType_t)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnIRSParamsSetSolverMainPrecision");
			fprintf(stderr, "wrapper_cusolverDnIRSParamsSetSolverMainPrecision:%p\n", wrapper_cusolverDnIRSParamsSetSolverMainPrecision);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnIRSParamsSetSolverMainPrecision():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnIRSParamsSetSolverMainPrecision(params, solver_main_precision);
		return retval;
	}
}