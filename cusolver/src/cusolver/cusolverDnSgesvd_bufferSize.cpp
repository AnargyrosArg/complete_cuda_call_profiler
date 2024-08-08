#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnSgesvd_bufferSize)(cusolverDnHandle_t, int, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnSgesvd_bufferSize(cusolverDnHandle_t handle, int m, int n, int *lwork) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnSgesvd_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnSgesvd_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, int, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnSgesvd_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnSgesvd_bufferSize:%p\n", wrapper_cusolverDnSgesvd_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnSgesvd_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnSgesvd_bufferSize(handle, m, n, lwork);
		return retval;
	}
}