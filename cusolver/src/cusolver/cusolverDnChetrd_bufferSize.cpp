#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnChetrd_bufferSize)(cusolverDnHandle_t, cublasFillMode_t, int, const cuComplex *, int, const float *, const float *, const cuComplex *, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnChetrd_bufferSize(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, const cuComplex *A, int lda, const float *d, const float *e, const cuComplex *tau, int *lwork) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnChetrd_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnChetrd_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasFillMode_t, int, const cuComplex *, int, const float *, const float *, const cuComplex *, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnChetrd_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnChetrd_bufferSize:%p\n", wrapper_cusolverDnChetrd_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnChetrd_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnChetrd_bufferSize(handle, uplo, n, A, lda, d, e, tau, lwork);
		return retval;
	}
}