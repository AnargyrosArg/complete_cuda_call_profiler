#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnGetStream)(cusolverDnHandle_t, cudaStream_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnGetStream(cusolverDnHandle_t handle, cudaStream_t *streamId) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnGetStream)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnGetStream = (cusolverStatus_t (*)(cusolverDnHandle_t, cudaStream_t *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnGetStream");
			fprintf(stderr, "wrapper_cusolverDnGetStream:%p\n", wrapper_cusolverDnGetStream);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnGetStream():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnGetStream(handle, streamId);
		return retval;
	}
}