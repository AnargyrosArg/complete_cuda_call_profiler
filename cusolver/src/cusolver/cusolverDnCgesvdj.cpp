#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnCgesvdj)(cusolverDnHandle_t, cusolverEigMode_t, int, int, int, cuComplex *, int, float *, cuComplex *, int, cuComplex *, int, cuComplex *, int, int *, gesvdjInfo_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnCgesvdj(cusolverDnHandle_t handle, cusolverEigMode_t jobz, int econ, int m, int n, cuComplex *A, int lda, float *S, cuComplex *U, int ldu, cuComplex *V, int ldv, cuComplex *work, int lwork, int *info, gesvdjInfo_t params) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnCgesvdj)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnCgesvdj = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverEigMode_t, int, int, int, cuComplex *, int, float *, cuComplex *, int, cuComplex *, int, cuComplex *, int, int *, gesvdjInfo_t)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnCgesvdj");
			fprintf(stderr, "wrapper_cusolverDnCgesvdj:%p\n", wrapper_cusolverDnCgesvdj);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnCgesvdj():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnCgesvdj(handle, jobz, econ, m, n, A, lda, S, U, ldu, V, ldv, work, lwork, info, params);
		return retval;
	}
}