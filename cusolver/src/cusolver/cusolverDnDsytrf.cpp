#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnDsytrf)(cusolverDnHandle_t, cublasFillMode_t, int, double *, int, int *, double *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnDsytrf(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, double *A, int lda, int *ipiv, double *work, int lwork, int *info) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnDsytrf)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnDsytrf = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasFillMode_t, int, double *, int, int *, double *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnDsytrf");
			fprintf(stderr, "wrapper_cusolverDnDsytrf:%p\n", wrapper_cusolverDnDsytrf);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnDsytrf():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnDsytrf(handle, uplo, n, A, lda, ipiv, work, lwork, info);
		return retval;
	}
}