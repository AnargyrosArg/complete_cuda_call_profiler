#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnDgeqrf)(cusolverDnHandle_t, int, int, double *, int, double *, double *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnDgeqrf(cusolverDnHandle_t handle, int m, int n, double *A, int lda, double *TAU, double *Workspace, int Lwork, int *devInfo) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnDgeqrf)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnDgeqrf = (cusolverStatus_t (*)(cusolverDnHandle_t, int, int, double *, int, double *, double *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnDgeqrf");
			fprintf(stderr, "wrapper_cusolverDnDgeqrf:%p\n", wrapper_cusolverDnDgeqrf);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnDgeqrf():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnDgeqrf(handle, m, n, A, lda, TAU, Workspace, Lwork, devInfo);
		return retval;
	}
}