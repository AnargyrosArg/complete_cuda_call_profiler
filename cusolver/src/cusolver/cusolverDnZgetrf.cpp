#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnZgetrf)(cusolverDnHandle_t, int, int, cuDoubleComplex *, int, cuDoubleComplex *, int *, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnZgetrf(cusolverDnHandle_t handle, int m, int n, cuDoubleComplex *A, int lda, cuDoubleComplex *Workspace, int *devIpiv, int *devInfo) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnZgetrf)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnZgetrf = (cusolverStatus_t (*)(cusolverDnHandle_t, int, int, cuDoubleComplex *, int, cuDoubleComplex *, int *, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnZgetrf");
			fprintf(stderr, "wrapper_cusolverDnZgetrf:%p\n", wrapper_cusolverDnZgetrf);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnZgetrf():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnZgetrf(handle, m, n, A, lda, Workspace, devIpiv, devInfo);
		return retval;
	}
}