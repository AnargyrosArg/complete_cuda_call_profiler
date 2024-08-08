#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverGetVersion)(int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverGetVersion(int *version) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverGetVersion)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverGetVersion = (cusolverStatus_t (*)(int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverGetVersion");
			fprintf(stderr, "wrapper_cusolverGetVersion:%p\n", wrapper_cusolverGetVersion);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverGetVersion():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverGetVersion(version);
		return retval;
	}
}