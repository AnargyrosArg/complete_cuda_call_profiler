#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnDestroyGesvdjInfo)(gesvdjInfo_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnDestroyGesvdjInfo(gesvdjInfo_t info) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnDestroyGesvdjInfo)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnDestroyGesvdjInfo = (cusolverStatus_t (*)(gesvdjInfo_t)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnDestroyGesvdjInfo");
			fprintf(stderr, "wrapper_cusolverDnDestroyGesvdjInfo:%p\n", wrapper_cusolverDnDestroyGesvdjInfo);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnDestroyGesvdjInfo():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnDestroyGesvdjInfo(info);
		return retval;
	}
}