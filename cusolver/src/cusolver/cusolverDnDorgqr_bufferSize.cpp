#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnDorgqr_bufferSize)(cusolverDnHandle_t, int, int, int, const double *, int, const double *, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnDorgqr_bufferSize(cusolverDnHandle_t handle, int m, int n, int k, const double *A, int lda, const double *tau, int *lwork) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnDorgqr_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnDorgqr_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, int, int, int, const double *, int, const double *, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnDorgqr_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnDorgqr_bufferSize:%p\n", wrapper_cusolverDnDorgqr_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnDorgqr_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnDorgqr_bufferSize(handle, m, n, k, A, lda, tau, lwork);
		return retval;
	}
}