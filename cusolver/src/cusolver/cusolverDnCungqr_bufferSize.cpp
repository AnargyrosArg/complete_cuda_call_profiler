#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnCungqr_bufferSize)(cusolverDnHandle_t, int, int, int, const cuComplex *, int, const cuComplex *, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnCungqr_bufferSize(cusolverDnHandle_t handle, int m, int n, int k, const cuComplex *A, int lda, const cuComplex *tau, int *lwork) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnCungqr_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnCungqr_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, int, int, int, const cuComplex *, int, const cuComplex *, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnCungqr_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnCungqr_bufferSize:%p\n", wrapper_cusolverDnCungqr_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnCungqr_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnCungqr_bufferSize(handle, m, n, k, A, lda, tau, lwork);
		return retval;
	}
}