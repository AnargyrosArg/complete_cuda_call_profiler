#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnIRSInfosGetOuterNiters)(cusolverDnIRSInfos_t, cusolver_int_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnIRSInfosGetOuterNiters(cusolverDnIRSInfos_t infos, cusolver_int_t *outer_niters) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnIRSInfosGetOuterNiters)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnIRSInfosGetOuterNiters = (cusolverStatus_t (*)(cusolverDnIRSInfos_t, cusolver_int_t *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnIRSInfosGetOuterNiters");
			fprintf(stderr, "wrapper_cusolverDnIRSInfosGetOuterNiters:%p\n", wrapper_cusolverDnIRSInfosGetOuterNiters);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnIRSInfosGetOuterNiters():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnIRSInfosGetOuterNiters(infos, outer_niters);
		return retval;
	}
}