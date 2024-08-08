#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnIRSXgels_bufferSize)(cusolverDnHandle_t, cusolverDnIRSParams_t, cusolver_int_t, cusolver_int_t, cusolver_int_t, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnIRSXgels_bufferSize(cusolverDnHandle_t handle, cusolverDnIRSParams_t params, cusolver_int_t m, cusolver_int_t n, cusolver_int_t nrhs, size_t *lwork_bytes) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnIRSXgels_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnIRSXgels_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverDnIRSParams_t, cusolver_int_t, cusolver_int_t, cusolver_int_t, size_t *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnIRSXgels_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnIRSXgels_bufferSize:%p\n", wrapper_cusolverDnIRSXgels_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnIRSXgels_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnIRSXgels_bufferSize(handle, params, m, n, nrhs, lwork_bytes);
		return retval;
	}
}