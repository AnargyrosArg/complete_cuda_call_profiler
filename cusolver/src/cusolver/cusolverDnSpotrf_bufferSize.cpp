#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnSpotrf_bufferSize)(cusolverDnHandle_t, cublasFillMode_t, int, float *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnSpotrf_bufferSize(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, float *A, int lda, int *Lwork) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnSpotrf_bufferSize)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnSpotrf_bufferSize = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasFillMode_t, int, float *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnSpotrf_bufferSize");
			fprintf(stderr, "wrapper_cusolverDnSpotrf_bufferSize:%p\n", wrapper_cusolverDnSpotrf_bufferSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnSpotrf_bufferSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnSpotrf_bufferSize(handle, uplo, n, A, lda, Lwork);
		return retval;
	}
}