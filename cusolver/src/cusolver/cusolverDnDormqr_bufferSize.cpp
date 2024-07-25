#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnDormqr_bufferSize)(cusolverDnHandle_t, cublasSideMode_t, cublasOperation_t, int, int, int, const double *, int, const double *, const double *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnDormqr_bufferSize(cusolverDnHandle_t handle, cublasSideMode_t side, cublasOperation_t trans, int m, int n, int k, const double *A, int lda, const double *tau, const double *C, int ldc, int *lwork) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnDormqr_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnDormqr_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasSideMode_t, cublasOperation_t, int, int, int, const double *, int, const double *, const double *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnDormqr_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnDormqr_bufferSize:%p\n", wrapper_cusolverDnDormqr_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnDormqr_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnDormqr_bufferSize(handle, side, trans, m, n, k, A, lda, tau, C, ldc, lwork);
		return retval;
	}
}