#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnSlauum)(cusolverDnHandle_t, cublasFillMode_t, int, float *, int, float *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnSlauum(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, float *A, int lda, float *work, int lwork, int *devInfo) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnSlauum)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnSlauum = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasFillMode_t, int, float *, int, float *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnSlauum");
			fprintf(stderr, "wrapper_cusolverDnSlauum:%p\n", wrapper_cusolverDnSlauum);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnSlauum():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnSlauum(handle, uplo, n, A, lda, work, lwork, devInfo);
		return retval;
	}
}