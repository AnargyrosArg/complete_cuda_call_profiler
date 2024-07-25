#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnZungtr_bufferSize)(cusolverDnHandle_t, cublasFillMode_t, int, const cuDoubleComplex *, int, const cuDoubleComplex *, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnZungtr_bufferSize(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, const cuDoubleComplex *A, int lda, const cuDoubleComplex *tau, int *lwork) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnZungtr_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnZungtr_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasFillMode_t, int, const cuDoubleComplex *, int, const cuDoubleComplex *, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnZungtr_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnZungtr_bufferSize:%p\n", wrapper_cusolverDnZungtr_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnZungtr_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnZungtr_bufferSize(handle, uplo, n, A, lda, tau, lwork);
		return retval;
	}
}