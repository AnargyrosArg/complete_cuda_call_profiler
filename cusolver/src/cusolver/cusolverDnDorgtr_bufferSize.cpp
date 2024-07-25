#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnDorgtr_bufferSize)(cusolverDnHandle_t, cublasFillMode_t, int, const double *, int, const double *, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnDorgtr_bufferSize(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, const double *A, int lda, const double *tau, int *lwork) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnDorgtr_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnDorgtr_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasFillMode_t, int, const double *, int, const double *, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnDorgtr_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnDorgtr_bufferSize:%p\n", wrapper_cusolverDnDorgtr_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnDorgtr_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnDorgtr_bufferSize(handle, uplo, n, A, lda, tau, lwork);
		return retval;
	}
}