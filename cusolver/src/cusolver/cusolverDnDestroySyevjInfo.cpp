#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnDestroySyevjInfo)(syevjInfo_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnDestroySyevjInfo(syevjInfo_t info) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnDestroySyevjInfo)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnDestroySyevjInfo = (cusolverStatus_t (*)(syevjInfo_t)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnDestroySyevjInfo");
			fprintf(stderr, "wrapper_cusolverDnDestroySyevjInfo:%p\n", wrapper_cusolverDnDestroySyevjInfo);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnDestroySyevjInfo():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnDestroySyevjInfo(info);
		return retval;
	}
}