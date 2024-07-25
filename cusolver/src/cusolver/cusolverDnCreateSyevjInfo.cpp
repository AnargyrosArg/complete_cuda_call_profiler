#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnCreateSyevjInfo)(syevjInfo_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnCreateSyevjInfo(syevjInfo_t *info) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnCreateSyevjInfo)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnCreateSyevjInfo = (cusolverStatus_t (*)(syevjInfo_t *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnCreateSyevjInfo");
			fprintf(stderr, "wrapper_cusolverDnCreateSyevjInfo:%p\n", wrapper_cusolverDnCreateSyevjInfo);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnCreateSyevjInfo():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnCreateSyevjInfo(info);
		return retval;
	}
}