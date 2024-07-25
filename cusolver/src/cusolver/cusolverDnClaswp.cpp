#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnClaswp)(cusolverDnHandle_t, int, cuComplex *, int, int, int, const int *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnClaswp(cusolverDnHandle_t handle, int n, cuComplex *A, int lda, int k1, int k2, const int *devIpiv, int incx) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnClaswp)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnClaswp = (cusolverStatus_t (*)(cusolverDnHandle_t, int, cuComplex *, int, int, int, const int *, int)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnClaswp");
			fprintf(stderr, "wrapper_cusolverDnClaswp:%p\n", wrapper_cusolverDnClaswp);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnClaswp():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnClaswp(handle, n, A, lda, k1, k2, devIpiv, incx);
		return retval;
	}
}