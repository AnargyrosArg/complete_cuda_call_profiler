#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnCgetrf)(cusolverDnHandle_t, int, int, cuComplex *, int, cuComplex *, int *, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnCgetrf(cusolverDnHandle_t handle, int m, int n, cuComplex *A, int lda, cuComplex *Workspace, int *devIpiv, int *devInfo) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnCgetrf)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnCgetrf = (cusolverStatus_t (*)(cusolverDnHandle_t, int, int, cuComplex *, int, cuComplex *, int *, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnCgetrf");
			fprintf(stderr, "wrapper_cusolverDnCgetrf:%p\n", wrapper_cusolverDnCgetrf);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnCgetrf():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnCgetrf(handle, m, n, A, lda, Workspace, devIpiv, devInfo);
		return retval;
	}
}