#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnZlaswp)(cusolverDnHandle_t, int, cuDoubleComplex *, int, int, int, const int *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnZlaswp(cusolverDnHandle_t handle, int n, cuDoubleComplex *A, int lda, int k1, int k2, const int *devIpiv, int incx) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnZlaswp)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnZlaswp = (cusolverStatus_t (*)(cusolverDnHandle_t, int, cuDoubleComplex *, int, int, int, const int *, int)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnZlaswp");
			fprintf(stderr, "wrapper_cusolverDnZlaswp:%p\n", wrapper_cusolverDnZlaswp);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnZlaswp():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnZlaswp(handle, n, A, lda, k1, k2, devIpiv, incx);
		return retval;
	}
}