#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnCpotrf)(cusolverDnHandle_t, cublasFillMode_t, int, cuComplex *, int, cuComplex *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnCpotrf(cusolverDnHandle_t handle, cublasFillMode_t uplo, int n, cuComplex *A, int lda, cuComplex *Workspace, int Lwork, int *devInfo) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnCpotrf)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnCpotrf = (cusolverStatus_t (*)(cusolverDnHandle_t, cublasFillMode_t, int, cuComplex *, int, cuComplex *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnCpotrf");
			fprintf(stderr, "wrapper_cusolverDnCpotrf:%p\n", wrapper_cusolverDnCpotrf);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnCpotrf():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnCpotrf(handle, uplo, n, A, lda, Workspace, Lwork, devInfo);
		return retval;
	}
}