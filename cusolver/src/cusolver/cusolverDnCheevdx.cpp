#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnCheevdx)(cusolverDnHandle_t, cusolverEigMode_t, cusolverEigRange_t, cublasFillMode_t, int, cuComplex *, int, float, float, int, int, int *, float *, cuComplex *, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnCheevdx(cusolverDnHandle_t handle, cusolverEigMode_t jobz, cusolverEigRange_t range, cublasFillMode_t uplo, int n, cuComplex *A, int lda, float vl, float vu, int il, int iu, int *meig, float *W, cuComplex *work, int lwork, int *info) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnCheevdx)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnCheevdx = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverEigMode_t, cusolverEigRange_t, cublasFillMode_t, int, cuComplex *, int, float, float, int, int, int *, float *, cuComplex *, int, int *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnCheevdx");
			fprintf(stderr, "wrapper_cusolverDnCheevdx:%p\n", wrapper_cusolverDnCheevdx);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnCheevdx():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnCheevdx(handle, jobz, range, uplo, n, A, lda, vl, vu, il, iu, meig, W, work, lwork, info);
		return retval;
	}
}