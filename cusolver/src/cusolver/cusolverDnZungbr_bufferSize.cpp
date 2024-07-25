#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnZungbr_bufferSize)(cusolverDnHandle_t, cublasSideMode_t, int, int, int, const cuDoubleComplex *, int, const cuDoubleComplex *, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnZungbr_bufferSize(cusolverDnHandle_t handle, cublasSideMode_t side, int m, int n, int k, const cuDoubleComplex *A, int lda, const cuDoubleComplex *tau, int *lwork) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnZungbr_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnZungbr_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasSideMode_t, int, int, int, const cuDoubleComplex *, int, const cuDoubleComplex *, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnZungbr_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnZungbr_bufferSize:%p\n", wrapper_cusolverDnZungbr_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnZungbr_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnZungbr_bufferSize(handle, side, m, n, k, A, lda, tau, lwork);
		return retval;
	}
}