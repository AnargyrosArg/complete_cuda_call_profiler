#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnZungtr)(cusolverDnHandle_t, cublasFillMode_t, int, cuDoubleComplex *, int, const cuDoubleComplex *, cuDoubleComplex *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnZungtr(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, cuDoubleComplex *A, int lda, const cuDoubleComplex *tau, cuDoubleComplex *work, int lwork, int *info) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnZungtr)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnZungtr = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasFillMode_t, int, cuDoubleComplex *, int, const cuDoubleComplex *, cuDoubleComplex *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnZungtr");
			fprintf(stderr, "wrapper_cusolverDnZungtr:%p\n", wrapper_cusolverDnZungtr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnZungtr():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnZungtr(handle, uplo, n, A, lda, tau, work, lwork, info);
		return retval;
	}
}