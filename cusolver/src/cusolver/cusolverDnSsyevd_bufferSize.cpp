#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnSsyevd_bufferSize)(cusolverDnHandle_t, cusolverEigMode_t, cublasFillMode_t, int, const float *, int, const float *, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnSsyevd_bufferSize(cusolverDnHandle_t handle, cusolverEigMode_t jobz, cublasFillMode_t uplo, int n, const float *A, int lda, const float *W, int *lwork) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnSsyevd_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnSsyevd_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverEigMode_t, cublasFillMode_t, int, const float *, int, const float *, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnSsyevd_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnSsyevd_bufferSize:%p\n", wrapper_cusolverDnSsyevd_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnSsyevd_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnSsyevd_bufferSize(handle, jobz, uplo, n, A, lda, W, lwork);
		return retval;
	}
}