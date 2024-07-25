#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnZsytrf)(cusolverDnHandle_t, cublasFillMode_t, int, cuDoubleComplex *, int, int *, cuDoubleComplex *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnZsytrf(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, cuDoubleComplex *A, int lda, int *ipiv, cuDoubleComplex *work, int lwork, int *info) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnZsytrf)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnZsytrf = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasFillMode_t, int, cuDoubleComplex *, int, int *, cuDoubleComplex *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnZsytrf");
			fprintf(stderr, "wrapper_cusolverDnZsytrf:%p\n", wrapper_cusolverDnZsytrf);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnZsytrf():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnZsytrf(handle, uplo, n, A, lda, ipiv, work, lwork, info);
		return retval;
	}
}