#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnSpotrs)(cusolverDnHandle_t, cublasFillMode_t, int, int, const float *, int, float *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnSpotrs(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, int nrhs, const float *A, int lda, float *B, int ldb, int *devInfo) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnSpotrs)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnSpotrs = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasFillMode_t, int, int, const float *, int, float *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnSpotrs");
			fprintf(stderr, "wrapper_cusolverDnSpotrs:%p\n", wrapper_cusolverDnSpotrs);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnSpotrs():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnSpotrs(handle, uplo, n, nrhs, A, lda, B, ldb, devInfo);
		return retval;
	}
}