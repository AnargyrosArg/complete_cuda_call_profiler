#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnSgeqrf)(cusolverDnHandle_t, int, int, float *, int, float *, float *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnSgeqrf(cusolverDnHandle_t handle, int m, int n, float *A, int lda, float *TAU, float *Workspace, int Lwork, int *devInfo) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnSgeqrf)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnSgeqrf = (cusolverStatus_t (*)(cusolverDnHandle_t, int, int, float *, int, float *, float *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnSgeqrf");
			fprintf(stderr, "wrapper_cusolverDnSgeqrf:%p\n", wrapper_cusolverDnSgeqrf);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnSgeqrf():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnSgeqrf(handle, m, n, A, lda, TAU, Workspace, Lwork, devInfo);
		return retval;
	}
}