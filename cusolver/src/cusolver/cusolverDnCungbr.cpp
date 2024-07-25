#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnCungbr)(cusolverDnHandle_t, cublasSideMode_t, int, int, int, cuComplex *, int, const cuComplex *, cuComplex *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnCungbr(cusolverDnHandle_t handle, cublasSideMode_t side, int m, int n, int k, cuComplex *A, int lda, const cuComplex *tau, cuComplex *work, int lwork, int *info) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnCungbr)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnCungbr = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasSideMode_t, int, int, int, cuComplex *, int, const cuComplex *, cuComplex *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnCungbr");
			fprintf(stderr, "wrapper_cusolverDnCungbr:%p\n", wrapper_cusolverDnCungbr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnCungbr():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnCungbr(handle, side, m, n, k, A, lda, tau, work, lwork, info);
		return retval;
	}
}