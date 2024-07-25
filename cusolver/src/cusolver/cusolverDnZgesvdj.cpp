#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnZgesvdj)(cusolverDnHandle_t, cusolverEigMode_t, int, int, int, cuDoubleComplex *, int, double *, cuDoubleComplex *, int, cuDoubleComplex *, int, cuDoubleComplex *, int, int *, gesvdjInfo_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnZgesvdj(cusolverDnHandle_t handle, cusolverEigMode_t jobz, int econ, int m, int n, cuDoubleComplex *A, int lda, double *S, cuDoubleComplex *U, int ldu, cuDoubleComplex *V, int ldv, cuDoubleComplex *work, int lwork, int *info, gesvdjInfo_t params) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnZgesvdj)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnZgesvdj = (cusolverStatus_t (*)(cusolverDnHandle_t, cusolverEigMode_t, int, int, int, cuDoubleComplex *, int, double *, cuDoubleComplex *, int, cuDoubleComplex *, int, cuDoubleComplex *, int, int *, gesvdjInfo_t)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnZgesvdj");
			fprintf(stderr, "wrapper_cusolverDnZgesvdj:%p\n", wrapper_cusolverDnZgesvdj);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnZgesvdj():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnZgesvdj(handle, jobz, econ, m, n, A, lda, S, U, ldu, V, ldv, work, lwork, info, params);
		return retval;
	}
}