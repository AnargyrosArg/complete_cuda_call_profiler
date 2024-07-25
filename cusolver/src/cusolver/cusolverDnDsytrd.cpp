#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnDsytrd)(cusolverDnHandle_t, cublasFillMode_t, int, double *, int, double *, double *, double *, double *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnDsytrd(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, double *A, int lda, double *d, double *e, double *tau, double *work, int lwork, int *info) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnDsytrd)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnDsytrd = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasFillMode_t, int, double *, int, double *, double *, double *, double *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnDsytrd");
			fprintf(stderr, "wrapper_cusolverDnDsytrd:%p\n", wrapper_cusolverDnDsytrd);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnDsytrd():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnDsytrd(handle, uplo, n, A, lda, d, e, tau, work, lwork, info);
		return retval;
	}
}