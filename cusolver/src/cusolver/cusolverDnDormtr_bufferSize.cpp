#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnDormtr_bufferSize)(cusolverDnHandle_t, cublasSideMode_t, cublasFillMode_t, cublasOperation_t, int, int, const double *, int, const double *, const double *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnDormtr_bufferSize(cusolverDnHandle_t handle, cublasSideMode_t side, cublasFillMode_t uplo, cublasOperation_t trans, int m, int n, const double *A, int lda, const double *tau, const double *C, int ldc, int *lwork) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnDormtr_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnDormtr_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasSideMode_t, cublasFillMode_t, cublasOperation_t, int, int, const double *, int, const double *, const double *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnDormtr_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnDormtr_bufferSize:%p\n", wrapper_cusolverDnDormtr_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnDormtr_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnDormtr_bufferSize(handle, side, uplo, trans, m, n, A, lda, tau, C, ldc, lwork);
		return retval;
	}
}