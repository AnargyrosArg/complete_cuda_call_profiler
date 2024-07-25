#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnDgetrf)(cusolverDnHandle_t, int, int, double *, int, double *, int *, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnDgetrf(cusolverDnHandle_t handle, int m, int n, double *A, int lda, double *Workspace, int *devIpiv, int *devInfo) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnDgetrf)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnDgetrf = (cusolverStatus_t (*)(cusolverDnHandle_t, int, int, double *, int, double *, int *, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnDgetrf");
			fprintf(stderr, "wrapper_cusolverDnDgetrf:%p\n", wrapper_cusolverDnDgetrf);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnDgetrf():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnDgetrf(handle, m, n, A, lda, Workspace, devIpiv, devInfo);
		return retval;
	}
}