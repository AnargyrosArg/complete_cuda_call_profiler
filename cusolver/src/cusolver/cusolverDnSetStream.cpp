#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnSetStream)(cusolverDnHandle_t, cudaStream_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnSetStream(cusolverDnHandle_t handle, cudaStream_t streamId) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnSetStream)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnSetStream = (cusolverStatus_t (*)(cusolverDnHandle_t, cudaStream_t)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnSetStream");
			fprintf(stderr, "wrapper_cusolverDnSetStream:%p\n", wrapper_cusolverDnSetStream);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnSetStream():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnSetStream(handle, streamId);
		return retval;
	}
}