#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnDlaswp)(cusolverDnHandle_t, int, double *, int, int, int, const int *, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnDlaswp(cusolverDnHandle_t handle, int n, double *A, int lda, int k1, int k2, const int *devIpiv, int incx) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnDlaswp)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnDlaswp = (cusolverStatus_t (*)(cusolverDnHandle_t, int, double *, int, int, int, const int *, int)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnDlaswp");
			fprintf(stderr, "wrapper_cusolverDnDlaswp:%p\n", wrapper_cusolverDnDlaswp);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnDlaswp():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnDlaswp(handle, n, A, lda, k1, k2, devIpiv, incx);
		return retval;
	}
}