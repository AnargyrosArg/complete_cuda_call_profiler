#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnSgebrd)(cusolverDnHandle_t, int, int, float *, int, float *, float *, float *, float *, float *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnSgebrd(cusolverDnHandle_t handle, int m, int n, float *A, int lda, float *D, float *E, float *TAUQ, float *TAUP, float *Work, int Lwork, int *devInfo) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnSgebrd)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnSgebrd = (cusolverStatus_t (*)(cusolverDnHandle_t, int, int, float *, int, float *, float *, float *, float *, float *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnSgebrd");
			fprintf(stderr, "wrapper_cusolverDnSgebrd:%p\n", wrapper_cusolverDnSgebrd);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnSgebrd():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnSgebrd(handle, m, n, A, lda, D, E, TAUQ, TAUP, Work, Lwork, devInfo);
		return retval;
	}
}