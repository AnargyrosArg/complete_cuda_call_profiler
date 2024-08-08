#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnIRSInfosDestroy)(cusolverDnIRSInfos_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnIRSInfosDestroy(cusolverDnIRSInfos_t infos) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnIRSInfosDestroy)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnIRSInfosDestroy = (cusolverStatus_t (*)(cusolverDnIRSInfos_t)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnIRSInfosDestroy");
			fprintf(stderr, "wrapper_cusolverDnIRSInfosDestroy:%p\n", wrapper_cusolverDnIRSInfosDestroy);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnIRSInfosDestroy():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnIRSInfosDestroy(infos);
		return retval;
	}
}