#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnDorgqr)(cusolverDnHandle_t, int, int, int, double *, int, const double *, double *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnDorgqr(cusolverDnHandle_t handle, int m, int n, int k, double *A, int lda, const double *tau, double *work, int lwork, int *info) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnDorgqr)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnDorgqr = (cusolverStatus_t (*)(cusolverDnHandle_t, int, int, int, double *, int, const double *, double *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnDorgqr");
			fprintf(stderr, "wrapper_cusolverDnDorgqr:%p\n", wrapper_cusolverDnDorgqr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnDorgqr():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnDorgqr(handle, m, n, k, A, lda, tau, work, lwork, info);
		return retval;
	}
}