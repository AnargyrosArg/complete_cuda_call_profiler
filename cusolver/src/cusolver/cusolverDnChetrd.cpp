#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnChetrd)(cusolverDnHandle_t, cublasFillMode_t, int, cuComplex *, int, float *, float *, cuComplex *, cuComplex *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnChetrd(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, cuComplex *A, int lda, float *d, float *e, cuComplex *tau, cuComplex *work, int lwork, int *info) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnChetrd)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnChetrd = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasFillMode_t, int, cuComplex *, int, float *, float *, cuComplex *, cuComplex *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnChetrd");
			fprintf(stderr, "wrapper_cusolverDnChetrd:%p\n", wrapper_cusolverDnChetrd);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnChetrd():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnChetrd(handle, uplo, n, A, lda, d, e, tau, work, lwork, info);
		return retval;
	}
}