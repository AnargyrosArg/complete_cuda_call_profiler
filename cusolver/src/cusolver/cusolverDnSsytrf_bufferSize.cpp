#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnSsytrf_bufferSize)(cusolverDnHandle_t, int, float *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnSsytrf_bufferSize(cusolverDnHandle_t handle, int n, float *A, int lda, int *lwork) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnSsytrf_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnSsytrf_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, int, float *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnSsytrf_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnSsytrf_bufferSize:%p\n", wrapper_cusolverDnSsytrf_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnSsytrf_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnSsytrf_bufferSize(handle, n, A, lda, lwork);
		return retval;
	}
}