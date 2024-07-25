#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnSpotri)(cusolverDnHandle_t, cublasFillMode_t, int, float *, int, float *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnSpotri(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, float *A, int lda, float *work, int lwork, int *devInfo) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnSpotri)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnSpotri = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasFillMode_t, int, float *, int, float *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnSpotri");
			fprintf(stderr, "wrapper_cusolverDnSpotri:%p\n", wrapper_cusolverDnSpotri);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnSpotri():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnSpotri(handle, uplo, n, A, lda, work, lwork, devInfo);
		return retval;
	}
}