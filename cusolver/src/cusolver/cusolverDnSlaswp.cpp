#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnSlaswp)(cusolverDnHandle_t, int, float *, int, int, int, const int *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnSlaswp(cusolverDnHandle_t handle, int n, float *A, int lda, int k1, int k2, const int *devIpiv, int incx) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnSlaswp)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnSlaswp = (cusolverStatus_t (*)(cusolverDnHandle_t, int, float *, int, int, int, const int *, int)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnSlaswp");
			fprintf(stderr, "wrapper_cusolverDnSlaswp:%p\n", wrapper_cusolverDnSlaswp);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnSlaswp():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnSlaswp(handle, n, A, lda, k1, k2, devIpiv, incx);
		return retval;
	}
}