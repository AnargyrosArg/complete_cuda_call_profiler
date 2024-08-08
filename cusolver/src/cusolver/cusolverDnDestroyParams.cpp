#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnDestroyParams)(cusolverDnParams_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnDestroyParams(cusolverDnParams_t params) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnDestroyParams)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnDestroyParams = (cusolverStatus_t (*)(cusolverDnParams_t)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnDestroyParams");
			fprintf(stderr, "wrapper_cusolverDnDestroyParams:%p\n", wrapper_cusolverDnDestroyParams);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnDestroyParams():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnDestroyParams(params);
		return retval;
	}
}