#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnZgeqrf)(cusolverDnHandle_t, int, int, cuDoubleComplex *, int, cuDoubleComplex *, cuDoubleComplex *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnZgeqrf(cusolverDnHandle_t handle, int m, int n, cuDoubleComplex *A, int lda, cuDoubleComplex *TAU, cuDoubleComplex *Workspace, int Lwork, int *devInfo) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnZgeqrf)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnZgeqrf = (cusolverStatus_t (*)(cusolverDnHandle_t, int, int, cuDoubleComplex *, int, cuDoubleComplex *, cuDoubleComplex *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnZgeqrf");
			fprintf(stderr, "wrapper_cusolverDnZgeqrf:%p\n", wrapper_cusolverDnZgeqrf);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnZgeqrf():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnZgeqrf(handle, m, n, A, lda, TAU, Workspace, Lwork, devInfo);
		return retval;
	}
}