#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnCungbr_bufferSize)(cusolverDnHandle_t, cublasSideMode_t, int, int, int, const cuComplex *, int, const cuComplex *, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnCungbr_bufferSize(cusolverDnHandle_t handle, cublasSideMode_t side, int m, int n, int k, const cuComplex *A, int lda, const cuComplex *tau, int *lwork) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnCungbr_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnCungbr_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasSideMode_t, int, int, int, const cuComplex *, int, const cuComplex *, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnCungbr_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnCungbr_bufferSize:%p\n", wrapper_cusolverDnCungbr_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnCungbr_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnCungbr_bufferSize(handle, side, m, n, k, A, lda, tau, lwork);
		return retval;
	}
}