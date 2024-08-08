#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnSgetrf)(cusolverDnHandle_t, int, int, float *, int, float *, int *, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnSgetrf(cusolverDnHandle_t handle, int m, int n, float *A, int lda, float *Workspace, int *devIpiv, int *devInfo) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnSgetrf)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnSgetrf = (cusolverStatus_t (*)(cusolverDnHandle_t, int, int, float *, int, float *, int *, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnSgetrf");
			fprintf(stderr, "wrapper_cusolverDnSgetrf:%p\n", wrapper_cusolverDnSgetrf);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnSgetrf():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnSgetrf(handle, m, n, A, lda, Workspace, devIpiv, devInfo);
		return retval;
	}
}