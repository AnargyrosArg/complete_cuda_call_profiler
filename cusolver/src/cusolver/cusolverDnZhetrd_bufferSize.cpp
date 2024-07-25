#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnZhetrd_bufferSize)(cusolverDnHandle_t, cublasFillMode_t, int, const cuDoubleComplex *, int, const double *, const double *, const cuDoubleComplex *, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnZhetrd_bufferSize(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, const cuDoubleComplex *A, int lda, const double *d, const double *e, const cuDoubleComplex *tau, int *lwork) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnZhetrd_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnZhetrd_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasFillMode_t, int, const cuDoubleComplex *, int, const double *, const double *, const cuDoubleComplex *, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnZhetrd_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnZhetrd_bufferSize:%p\n", wrapper_cusolverDnZhetrd_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnZhetrd_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnZhetrd_bufferSize(handle, uplo, n, A, lda, d, e, tau, lwork);
		return retval;
	}
}