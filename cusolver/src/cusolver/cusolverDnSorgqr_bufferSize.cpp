#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnSorgqr_bufferSize)(cusolverDnHandle_t, int, int, int, const float *, int, const float *, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnSorgqr_bufferSize(cusolverDnHandle_t handle, int m, int n, int k, const float *A, int lda, const float *tau, int *lwork) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnSorgqr_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnSorgqr_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, int, int, int, const float *, int, const float *, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnSorgqr_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnSorgqr_bufferSize:%p\n", wrapper_cusolverDnSorgqr_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnSorgqr_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnSorgqr_bufferSize(handle, m, n, k, A, lda, tau, lwork);
		return retval;
	}
}