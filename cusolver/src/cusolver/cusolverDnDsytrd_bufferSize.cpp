#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnDsytrd_bufferSize)(cusolverDnHandle_t, cublasFillMode_t, int, const double *, int, const double *, const double *, const double *, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnDsytrd_bufferSize(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, const double *A, int lda, const double *d, const double *e, const double *tau, int *lwork) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnDsytrd_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnDsytrd_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasFillMode_t, int, const double *, int, const double *, const double *, const double *, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnDsytrd_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnDsytrd_bufferSize:%p\n", wrapper_cusolverDnDsytrd_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnDsytrd_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnDsytrd_bufferSize(handle, uplo, n, A, lda, d, e, tau, lwork);
		return retval;
	}
}