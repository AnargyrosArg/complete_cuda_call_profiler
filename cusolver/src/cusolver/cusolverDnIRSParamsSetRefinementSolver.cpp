#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnIRSParamsSetRefinementSolver)(cusolverDnIRSParams_t, cusolverIRSRefinement_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnIRSParamsSetRefinementSolver(cusolverDnIRSParams_t params, cusolverIRSRefinement_t refinement_solver) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnIRSParamsSetRefinementSolver)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnIRSParamsSetRefinementSolver = (cusolverStatus_t (*)(cusolverDnIRSParams_t, cusolverIRSRefinement_t)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnIRSParamsSetRefinementSolver");
			fprintf(stderr, "wrapper_cusolverDnIRSParamsSetRefinementSolver:%p\n", wrapper_cusolverDnIRSParamsSetRefinementSolver);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnIRSParamsSetRefinementSolver():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnIRSParamsSetRefinementSolver(params, refinement_solver);
		return retval;
	}
}