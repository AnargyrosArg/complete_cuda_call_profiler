#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnZungqr)(cusolverDnHandle_t, int, int, int, cuDoubleComplex *, int, const cuDoubleComplex *, cuDoubleComplex *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnZungqr(cusolverDnHandle_t handle, int m, int n, int k, cuDoubleComplex *A, int lda, const cuDoubleComplex *tau, cuDoubleComplex *work, int lwork, int *info) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnZungqr)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnZungqr = (cusolverStatus_t (*)(cusolverDnHandle_t, int, int, int, cuDoubleComplex *, int, const cuDoubleComplex *, cuDoubleComplex *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnZungqr");
			fprintf(stderr, "wrapper_cusolverDnZungqr:%p\n", wrapper_cusolverDnZungqr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnZungqr():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnZungqr(handle, m, n, k, A, lda, tau, work, lwork, info);
		return retval;
	}
}