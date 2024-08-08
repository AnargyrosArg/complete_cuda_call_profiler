#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnSsytrd)(cusolverDnHandle_t, cublasFillMode_t, int, float *, int, float *, float *, float *, float *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnSsytrd(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, float *A, int lda, float *d, float *e, float *tau, float *work, int lwork, int *info) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnSsytrd)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnSsytrd = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasFillMode_t, int, float *, int, float *, float *, float *, float *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnSsytrd");
			fprintf(stderr, "wrapper_cusolverDnSsytrd:%p\n", wrapper_cusolverDnSsytrd);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnSsytrd():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnSsytrd(handle, uplo, n, A, lda, d, e, tau, work, lwork, info);
		return retval;
	}
}