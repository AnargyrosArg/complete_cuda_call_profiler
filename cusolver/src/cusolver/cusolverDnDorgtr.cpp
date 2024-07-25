#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnDorgtr)(cusolverDnHandle_t, cublasFillMode_t, int, double *, int, const double *, double *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnDorgtr(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, double *A, int lda, const double *tau, double *work, int lwork, int *info) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnDorgtr)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnDorgtr = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasFillMode_t, int, double *, int, const double *, double *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnDorgtr");
			fprintf(stderr, "wrapper_cusolverDnDorgtr:%p\n", wrapper_cusolverDnDorgtr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnDorgtr():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnDorgtr(handle, uplo, n, A, lda, tau, work, lwork, info);
		return retval;
	}
}