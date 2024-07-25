#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnCreateGesvdjInfo)(gesvdjInfo_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnCreateGesvdjInfo(gesvdjInfo_t *info) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnCreateGesvdjInfo)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnCreateGesvdjInfo = (cusolverStatus_t (*)(gesvdjInfo_t *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnCreateGesvdjInfo");
			fprintf(stderr, "wrapper_cusolverDnCreateGesvdjInfo:%p\n", wrapper_cusolverDnCreateGesvdjInfo);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnCreateGesvdjInfo():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnCreateGesvdjInfo(info);
		return retval;
	}
}