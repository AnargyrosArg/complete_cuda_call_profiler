#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnSsytrd_bufferSize)(cusolverDnHandle_t, cublasFillMode_t, int, const float *, int, const float *, const float *, const float *, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnSsytrd_bufferSize(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, const float *A, int lda, const float *d, const float *e, const float *tau, int *lwork) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnSsytrd_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnSsytrd_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasFillMode_t, int, const float *, int, const float *, const float *, const float *, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnSsytrd_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnSsytrd_bufferSize:%p\n", wrapper_cusolverDnSsytrd_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnSsytrd_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnSsytrd_bufferSize(handle, uplo, n, A, lda, d, e, tau, lwork);
		return retval;
	}
}