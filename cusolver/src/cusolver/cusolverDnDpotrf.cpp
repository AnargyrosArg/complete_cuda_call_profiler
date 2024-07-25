#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnDpotrf)(cusolverDnHandle_t, cublasFillMode_t, int, double *, int, double *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnDpotrf(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, double *A, int lda, double *Workspace, int Lwork, int *devInfo) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnDpotrf)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnDpotrf = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasFillMode_t, int, double *, int, double *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnDpotrf");
			fprintf(stderr, "wrapper_cusolverDnDpotrf:%p\n", wrapper_cusolverDnDpotrf);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnDpotrf():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnDpotrf(handle, uplo, n, A, lda, Workspace, Lwork, devInfo);
		return retval;
	}
}