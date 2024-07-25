#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnDsyevd)(cusolverDnHandle_t, cusolverEigMode_t, cublasFillMode_t, int, double *, int, double *, double *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnDsyevd(cusolverDnHandle_t handle, cusolverEigMode_t jobz, cublasFillMode_t uplo, int n, double *A, int lda, double *W, double *work, int lwork, int *info) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnDsyevd)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnDsyevd = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverEigMode_t, cublasFillMode_t, int, double *, int, double *, double *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnDsyevd");
			fprintf(stderr, "wrapper_cusolverDnDsyevd:%p\n", wrapper_cusolverDnDsyevd);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnDsyevd():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnDsyevd(handle, jobz, uplo, n, A, lda, W, work, lwork, info);
		return retval;
	}
}