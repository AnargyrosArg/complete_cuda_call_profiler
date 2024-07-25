#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnDpotrs)(cusolverDnHandle_t, cublasFillMode_t, int, int, const double *, int, double *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnDpotrs(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, int nrhs, const double *A, int lda, double *B, int ldb, int *devInfo) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnDpotrs)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnDpotrs = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasFillMode_t, int, int, const double *, int, double *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnDpotrs");
			fprintf(stderr, "wrapper_cusolverDnDpotrs:%p\n", wrapper_cusolverDnDpotrs);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnDpotrs():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnDpotrs(handle, uplo, n, nrhs, A, lda, B, ldb, devInfo);
		return retval;
	}
}